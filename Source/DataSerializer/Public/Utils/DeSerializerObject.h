// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DeSerializerObject.generated.h"

/**
 * @class UDeSerializerObject
 * @brief A class responsible for deserializing data from a memory buffer.
 * 
 * This class provides various functions to read different data types from a memory buffer.
 */
UCLASS(Blueprintable, BlueprintType)
class DATASERIALIZER_API UDeSerializerObject : public UObject
{
	GENERATED_BODY()

public:
	/** Default constructor. */
	UDeSerializerObject();

protected:
	/** Memory reader used to deserialize data from a buffer. */
	TSharedPtr<FMemoryReader> MemoryReader;

protected:
	/**
	 * Gets a reference to the memory reader.
	 * @return A reference to the FMemoryReader instance.
	 */
	FMemoryReader& GetMemoryReaderRef() const;

public:
	/**
	 * Clears the current deserialization state.
	 * @note This function resets the memory reader and any deserialized data.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject")
	virtual void Clear();

	/**
	 * Starts the deserialization process with the provided byte array.
	 * @param InBytes The array of bytes to deserialize.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject")
	virtual void Start(const TArray<uint8>& InBytes);


	/**
	 * Attempts to read a value of type T from the memory buffer.
	 * @tparam T The type of the value to read.
	 * @param OutValue Reference to the variable where the read value will be stored.
	 * @return true if the value was successfully read; false otherwise.
	 */
	template <typename T>
	bool TryReadT(T& OutValue)
	{
		if (!MemoryReader.IsValid())
			return false;

		FMemoryReader& reader = GetMemoryReaderRef();
		T value;
		reader << value;

		if (reader.IsError() || reader.IsCriticalError())
			return false;

		OutValue = value;
		return true;
	}

public:
	
	/**
	 * Tries to read an int32 value from the buffer.
	 * @param OutInt Reference to the int32 variable where the read value will be stored.
	 * @return true if the int32 value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadInt(int32& OutInt);

	/**
	 * Tries to read an int64 value from the buffer.
	 * @param OutInt64 Reference to the int64 variable where the read value will be stored.
	 * @return true if the int64 value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadInt64(int64& OutInt64);

	/**
	 * Tries to read a float value from the buffer.
	 * @param OutFloat Reference to the float variable where the read value will be stored.
	 * @return true if the float value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadFloat(float& OutFloat);

	/**
	 * Tries to read a double value from the buffer.
	 * @param OutDouble Reference to the double variable where the read value will be stored.
	 * @return true if the double value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadDouble(double& OutDouble);

	/**
	 * Tries to read a boolean value from the buffer.
	 * @param OutBool Reference to the boolean variable where the read value will be stored.
	 * @return true if the boolean value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadBool(bool& OutBool);

	/**
	 * Tries to read a uint8 value from the buffer.
	 * @param OutUInt8 Reference to the uint8 variable where the read value will be stored.
	 * @return true if the uint8 value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadUInt8(uint8& OutUInt8);

	/**
	 * Tries to read an FVector value from the buffer.
	 * @param OutVector Reference to the FVector variable where the read value will be stored.
	 * @return true if the FVector value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadVector(FVector& OutVector);

	/**
	 * Tries to read an FIntVector value from the buffer.
	 * @param OutIntVector Reference to the FIntVector variable where the read value will be stored.
	 * @return true if the FIntVector value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadIntVector(FIntVector& OutIntVector);

	/**
	 * Tries to read an FVector2D value from the buffer.
	 * @param OutVector2D Reference to the FVector2D variable where the read value will be stored.
	 * @return true if the FVector2D value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadVector2D(FVector2D& OutVector2D);

	/**
	 * Tries to read an FIntPoint value from the buffer.
	 * @param OutIntPoint Reference to the FIntPoint variable where the read value will be stored.
	 * @return true if the FIntPoint value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadIntPoint(FIntPoint& OutIntPoint);

	/**
	 * Tries to read an FRotator value from the buffer.
	 * @param OutRotator Reference to the FRotator variable where the read value will be stored.
	 * @return true if the FRotator value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadRotator(FRotator& OutRotator);

	/**
	 * Tries to read an FTransform value from the buffer.
	 * @param OutTransform Reference to the FTransform variable where the read value will be stored.
	 * @return true if the FTransform value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadTransform(FTransform& OutTransform);

	/**
	 * Tries to read an FString value from the buffer.
	 * @param OutString Reference to the FString variable where the read value will be stored.
	 * @return true if the FString value was successfully read; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="UDeSerializerObject|DeSerialization")
	virtual bool TryReadString(FString& OutString);
};
