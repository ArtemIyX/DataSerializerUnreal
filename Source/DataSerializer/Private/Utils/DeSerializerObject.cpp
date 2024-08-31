// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/DeSerializerObject.h"

#include "Libs/DataSerializerLib.h"

namespace Serializer
{
	FMemoryReader tempReader({});
}


UDeSerializerObject::UDeSerializerObject()
{
}

FMemoryReader& UDeSerializerObject::GetMemoryReaderRef() const
{
	if (MemoryReader.IsValid())
	{
		return *MemoryReader;
	}

	return Serializer::tempReader; // DONT DO THIS
}

void UDeSerializerObject::Clear()
{
	MemoryReader.Reset();
}

void UDeSerializerObject::Start(const TArray<uint8>& InBytes)
{
	Clear();
	MemoryReader = MakeShareable<FMemoryReader>(new FMemoryReader(InBytes));
}

bool UDeSerializerObject::TryReadInt(int32& OutInt) { return TryReadT(OutInt); }

bool UDeSerializerObject::TryReadInt64(int64& OutInt64) { return TryReadT(OutInt64); }

bool UDeSerializerObject::TryReadFloat(float& OutFloat) { return TryReadT(OutFloat); }

bool UDeSerializerObject::TryReadDouble(double& OutDouble) { return TryReadT(OutDouble); }

bool UDeSerializerObject::TryReadBool(bool& OutBool) { return TryReadT(OutBool); }

bool UDeSerializerObject::TryReadUInt8(uint8& OutUInt8) { return TryReadT(OutUInt8); }

bool UDeSerializerObject::TryReadVector(FVector& OutVector) { return TryReadT(OutVector); }

bool UDeSerializerObject::TryReadIntVector(FIntVector& OutIntVector) { return TryReadT(OutIntVector); }

bool UDeSerializerObject::TryReadVector2D(FVector2D& OutVector2D) { return TryReadT(OutVector2D); }

bool UDeSerializerObject::TryReadIntPoint(FIntPoint& OutIntPoint) { return TryReadT(OutIntPoint); }

bool UDeSerializerObject::TryReadRotator(FRotator& OutRotator) { return TryReadT(OutRotator); }

bool UDeSerializerObject::TryReadTransform(FTransform& OutTransform) { return TryReadT(OutTransform); }

bool UDeSerializerObject::TryReadString(FString& OutString) { return TryReadT(OutString); }

bool UDeSerializerObject::TryReadObject(UObject* InObjectOuter, UObject*& OutObject)
{
	FMemoryReader& memoryReader = GetMemoryReaderRef();
	return UDataSerializerLib::DeSerializeObjectCpp(memoryReader, InObjectOuter, OutObject);
}

bool UDeSerializerObject::TryReadObjects(UObject* InObjectOuter, TArray<UObject*>& OutObjects)
{
	FMemoryReader& memoryReader = GetMemoryReaderRef();
	return UDataSerializerLib::DeSerializeObjectsCpp(memoryReader, InObjectOuter, OutObjects);
}
