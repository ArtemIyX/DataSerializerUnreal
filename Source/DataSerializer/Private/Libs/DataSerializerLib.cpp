// Fill out your copyright notice in the Description page of Project Settings.


#include "Libs/DataSerializerLib.h"

#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"

bool UDataSerializerLib::WriteBytesToDisk(const TArray<uint8>& InBytes, FString InPath)
{
	return FFileHelper::SaveArrayToFile(InBytes, *InPath);
}

bool UDataSerializerLib::WriteBytesToDiskCompressed(const TArray<uint8>& InBytes, FString InPath)
{
	TArray<uint8> compressedData;
	FArchiveSaveCompressedProxy compresser(compressedData, NAME_Zlib);
	TArray<uint8> copy = InBytes;
	compresser << copy;
	compresser.Flush();
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
