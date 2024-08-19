// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataSerializerLib.generated.h"

constexpr int32 XEUS_SAVEGAME_FILE_TYPE_TAG = 0x78657573; //XEUS

USTRUCT()
struct FSerializationHeader
{
	GENERATED_BODY()
public:
	FSerializationHeader();
	FSerializationHeader(TSubclassOf<UObject> ObjectType);

	void Empty();

	void Read(FMemoryReader& MemoryReader);
	void Write(FMemoryWriter& MemoryWriter);
	
	FString GameClassName;
};

/**
 * Set of functions for working with data serialization and writing them to disk
 */
UCLASS(Blueprintable, BlueprintType)
class DATASERIALIZER_API UDataSerializerLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

#pragma region Disk

public:
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Disk")
	static bool WriteBytesToDisk(const TArray<uint8>& InBytes, FString InPath);
	
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Disk")
	static bool WriteBytesToDiskCompressed(const TArray<uint8>& InBytes, FString InPath);

	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Disk")
	static bool ReadBytesFromDisk(TArray<uint8>& OutBytes, FString InPath);

	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Disk")
	static bool ReadCompressedBytesFromDisk(TArray<uint8>& OutBytes, FString InPath);
	
#pragma endregion

#pragma region Serialize
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Serialization")
	static bool SerializeObject(TArray<uint8>& OutBytes, UObject* InObject);

	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Serialization")
	static bool DeserializeObject(const TArray<uint8>& InBytes, UObject* ObjectOuter, UObject*& OutObject);

	/* Will add N(num) before array of bytes */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Serialization")
	static bool SerializeObjects(TArray<uint8>& OutBytes, TArray<UObject*> InObjects);

	/* Require N(num) before array of bytes */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Serialization")
	static bool DeSerializeObjects(const TArray<uint8>& InBytes, UObject* InObjectOuter, TArray<UObject*>& OutObjects);
#pragma endregion 
	

#pragma region Utils
	static TArray<uint8> AppendBytes(const TArray<uint8>& InLeftPart, const TArray<uint8>& InRightPart);
#pragma endregion 
};
