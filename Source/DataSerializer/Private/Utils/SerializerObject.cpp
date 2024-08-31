// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/SerializerObject.h"

#include "Libs/DataSerializerLib.h"

USerializerObject::USerializerObject()
{
}

FMemoryWriter& USerializerObject::GetMemoryWriterRef()
{
	if (!MemoryWriter.IsValid())
	{
		Prepare();
	}
	return *MemoryWriter;
}

void USerializerObject::GetBytes(TArray<uint8>& OutBytes) { OutBytes = Bytes; }

void USerializerObject::SerializeInt(int32 InInteger) { GetMemoryWriterRef() << InInteger; }

void USerializerObject::SerializeBigInt(int64 InBigInt) { GetMemoryWriterRef() << InBigInt; }

void USerializerObject::SerializeFloat(float InFloat) { GetMemoryWriterRef() << InFloat; }

void USerializerObject::SerializeDouble(double InDouble) { GetMemoryWriterRef() << InDouble; }

void USerializerObject::SerializeBool(bool InBool) { GetMemoryWriterRef() << InBool; }

void USerializerObject::SerializeByte(uint8 InByte) { GetMemoryWriterRef() << InByte; }

void USerializerObject::SerializeVector(FVector InVector) { GetMemoryWriterRef() << InVector; }

void USerializerObject::SerializeIntVector(FIntVector InVector) { GetMemoryWriterRef() << InVector; }

void USerializerObject::SerializeVector2D(FVector2D InVector) { GetMemoryWriterRef() << InVector; }

void USerializerObject::SerializePoint(FIntPoint InPoint) { GetMemoryWriterRef() << InPoint; }

void USerializerObject::SerializeRotator(FRotator InRotator) { GetMemoryWriterRef() << InRotator; }

void USerializerObject::SerializeTransform(FTransform InTransform) { GetMemoryWriterRef() << InTransform; }

void USerializerObject::SerializeString(FString InString) { GetMemoryWriterRef() << InString; }

void USerializerObject::SerializeObject(UObject* InObject)
{
	if (!IsValid(InObject))
		return;
	TArray<uint8> bytes;
	UDataSerializerLib::SerializeObject(bytes, InObject);
	GetMemoryWriterRef() << bytes;
}

void USerializerObject::SerializeObjects(const TArray<UObject*>& InObjects)
{
	TArray<uint8> bytes;
	UDataSerializerLib::SerializeObjects(bytes, InObjects);
	GetMemoryWriterRef() << bytes;
}

void USerializerObject::PushBytes(const TArray<uint8>& InBytes)
{
	this->Bytes.Append(InBytes);
}

void USerializerObject::Clear()
{
	this->Bytes.Empty();
	this->MemoryWriter.Reset();
}

void USerializerObject::Prepare()
{
	Clear();
	this->MemoryWriter = MakeShareable<FMemoryWriter>(new FMemoryWriter(Bytes));
}
