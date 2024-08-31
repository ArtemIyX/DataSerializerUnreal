// Fill out your copyright notice in the Description page of Project Settings.


#include "Libs/DataSerializerLib.h"

#include "Math/BigInt.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

FSerializationHeader::FSerializationHeader()
{
}

FSerializationHeader::FSerializationHeader(TSubclassOf<UObject> ObjectType) :
	GameClassName(ObjectType->GetPathName())
{
}

void FSerializationHeader::Empty()
{
	GameClassName.Empty();
}

void FSerializationHeader::Read(FMemoryReader& MemoryReader)
{
	Empty();
	// Get the class name
	MemoryReader << GameClassName;
}

void FSerializationHeader::Write(FMemoryWriter& MemoryWriter)
{
	// Write the class name, so we know what class to load to
	MemoryWriter << GameClassName;
}

bool UDataSerializerLib::WriteBytesToDisk(const TArray<uint8>& InBytes, FString InPath)
{
	return FFileHelper::SaveArrayToFile(InBytes, *InPath);
}

bool UDataSerializerLib::WriteBytesToDiskCompressed(const TArray<uint8>& InBytes, FString InPath)
{
	ensure(InBytes.Num() > 0);
	TArray<uint8> compressedData;
	{
		FArchiveSaveCompressedProxy compresser(compressedData, NAME_Zlib);
		TArray<uint8> copy = InBytes;
		compresser << copy;
		compresser.Flush();
	}
	return WriteBytesToDisk(compressedData, InPath);
}

bool UDataSerializerLib::ReadBytesFromDisk(TArray<uint8>& OutBytes, FString InPath)
{
	return FFileHelper::LoadFileToArray(OutBytes, *InPath);
}

bool UDataSerializerLib::ReadCompressedBytesFromDisk(TArray<uint8>& OutBytes, FString InPath)
{
	TArray<uint8> compressedData;
	if (!ReadBytesFromDisk(compressedData, InPath))
		return false;

	FArchiveLoadCompressedProxy Decompressor(compressedData, NAME_Zlib);
	if (Decompressor.GetError())
		return false;

	Decompressor << OutBytes;

	if (Decompressor.GetError())
		return false;
	return true;
}

bool UDataSerializerLib::SerializeObject(TArray<uint8>& OutBytes, UObject* InObject)
{
	ensure(IsValid(InObject));
	OutBytes.Empty();
	FMemoryWriter writer(OutBytes, true);

	FSerializationHeader header(InObject->GetClass());
	header.Write(writer);

	// Then save the object state, replacing object refs and names with strings
	FObjectAndNameAsStringProxyArchive archive(writer, false);
	InObject->Serialize(archive);

	if (archive.GetError())
		return false;

	return true;
}

bool UDataSerializerLib::DeserializeObject(const TArray<uint8>& InBytes, UObject* ObjectOuter, UObject*& OutObject)
{
	ensure(IsValid(ObjectOuter));
	ensure(InBytes.Num() > 0);
	OutObject = nullptr;
	FMemoryReader reader(InBytes, true);

	return DeSerializeObjectCpp(reader, ObjectOuter, OutObject);
}

bool UDataSerializerLib::DeSerializeObjectCpp(FMemoryReader& InReader,
                                              UObject* ObjectOuter, UObject*& OutObject)
{
	FSerializationHeader header;
	header.Read(InReader);

	// Try and find it, and failing that, load it
	UClass* gameClass = FindObject<UClass>(ANY_PACKAGE, *header.GameClassName);
	if (gameClass == nullptr)
	{
		gameClass = LoadObject<UClass>(nullptr, *header.GameClassName);
	}

	// If we have a class, try and load it.
	if (gameClass != nullptr)
	{
		OutObject = NewObject<UObject>(ObjectOuter, gameClass);

		FObjectAndNameAsStringProxyArchive archive(InReader, true);
		OutObject->Serialize(archive);
	}

	return IsValid(OutObject);
}

bool UDataSerializerLib::SerializeObjects(TArray<uint8>& OutBytes, TArray<UObject*> InObjects)
{
	ensure(InObjects.Num() > 0);
	OutBytes.Empty();
	FMemoryWriter writer(OutBytes, true);

	int32 n = InObjects.Num();
	writer << n;
	for (int32 i = 0; i < n; ++i)
	{
		FSerializationHeader SaveHeader(InObjects[i]->GetClass());
		SaveHeader.Write(writer);

		// Then save the object state, replacing object refs and names with strings
		FObjectAndNameAsStringProxyArchive Ar(writer, false);
		InObjects[i]->Serialize(Ar);

		if (Ar.GetError())
			return false;
	}

	return true;
}

bool UDataSerializerLib::DeSerializeObjects(const TArray<uint8>& InBytes, UObject* InObjectOuter,
                                            TArray<UObject*>& OutObjects)
{
	ensure(InBytes.Num() > 0);
	OutObjects.Empty();
	FMemoryReader reader(InBytes, true);

	return DeSerializeObjectsCpp(reader, InObjectOuter, OutObjects);
}

bool UDataSerializerLib::DeSerializeObjectsCpp(FMemoryReader& InReader,
                                               UObject* InObjectOuter, TArray<UObject*>& OutObjects)
{
	int32 n = 0;
	InReader << n;
	for (int32 i = 0; i < n; ++i)
	{
		FSerializationHeader header;
		header.Read(InReader);

		// Try and find it, and failing that, load it
		UClass* gameClass = FindObject<UClass>(ANY_PACKAGE, *header.GameClassName);
		if (gameClass == nullptr)
		{
			gameClass = LoadObject<UClass>(nullptr, *header.GameClassName);
		}

		// If we have a class, try and load it.
		if (gameClass != nullptr)
		{
			UObject* resObject = nullptr;
			resObject = NewObject<UObject>(InObjectOuter, gameClass);

			FObjectAndNameAsStringProxyArchive archive(InReader, true);
			resObject->Serialize(archive);
			OutObjects.Add(resObject);
		}
		else
		{
			return false;
		}
	}

	if (OutObjects.Num() != n)
	{
		return false;
	}

	return true;
}

void UDataSerializerLib::GetUtf8Bytes(const FString& InString, TArray<uint8>& OutBytes)
{
	// Convert FString to UTF-8 encoded string
	FTCHARToUTF8 Utf8Converter(*InString);
	// Resize the output array to match the size of the UTF-8 string
	OutBytes.SetNum(Utf8Converter.Length());

	// Copy the UTF-8 bytes to the output array
	FMemory::Memcpy(OutBytes.GetData(), Utf8Converter.Get(), Utf8Converter.Length());
}

FString UDataSerializerLib::Utf8BytesToString(const TArray<uint8>& InBytes)
{
	return FString(FUTF8ToTCHAR(reinterpret_cast<const ANSICHAR*>(InBytes.GetData()), InBytes.Num()));
}

TArray<uint8> UDataSerializerLib::AppendBytes(const TArray<uint8>& InLeftPart, const TArray<uint8>& InRightPart)
{
	TArray<uint8> arr = {InLeftPart};
	arr.Append(InRightPart);
	return arr;
}
