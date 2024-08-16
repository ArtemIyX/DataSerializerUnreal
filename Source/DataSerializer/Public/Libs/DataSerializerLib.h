// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataSerializerLib.generated.h"

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
};
