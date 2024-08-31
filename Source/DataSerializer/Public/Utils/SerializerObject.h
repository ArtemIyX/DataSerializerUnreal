// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SerializerObject.generated.h"

/**
 * @class USerializerObject
 * @brief A class for serializing various data types into a byte array for use in Unreal Engine.
 * 
 * The `USerializerObject` class provides functionality to serialize common data types into a byte array (`TArray<uint8>`).
 * It is designed to work within Unreal Engine and leverages the `FMemoryWriter` class to handle the byte serialization.
 * This class is Blueprintable and can be used directly in Unreal Engine Blueprints.
 * 
 * The class includes methods to serialize integers, floating point numbers, vectors, rotators, and transforms, 
 * as well as to clear the serialized data and prepare the writer for new data.
 */
UCLASS(Blueprintable, BlueprintType)
class DATASERIALIZER_API USerializerObject : public UObject
{
	GENERATED_BODY()

public:
	USerializerObject();

protected:
	/** 
	 * @brief Array of bytes representing the serialized data.
	 * 
	 * This array is populated with the serialized form of the data that is written using the various serialization methods.
	 */
	UPROPERTY(BlueprintReadOnly)
	TArray<uint8> Bytes;

	/** 
	 * @brief Shared pointer to a memory writer used for serialization.
	 * 
	 * The `FMemoryWriter` is used to write data into the `Bytes` array.
	 */
	TSharedPtr<FMemoryWriter> MemoryWriter;

protected:
	/**
	 * @brief Gets a reference to the memory writer.
	 * @note If MemoryWriter has not been set, then it will call the Prepare() method
	 * @see Prepare
	 * @see MemoryWriter
	 * 
	 * @return Reference to `FMemoryWriter`.
	 */
	virtual FMemoryWriter& GetMemoryWriterRef();

public:
	/**
	 * @brief Retrieves the serialized bytes.
	 * 
	 * @param OutBytes An array to store the retrieved bytes.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject")
	virtual void GetBytes(TArray<uint8>& OutBytes);

	/**
	 * @brief Appends input bytes to the current serialized data.
	 * 
	 * @param InBytes The array of bytes to append.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject")
	virtual void PushBytes(const TArray<uint8>& InBytes);

	/**
	 * @brief Clears the current serialized data and resets the writer.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject")
	virtual void Clear();

	/**
	 * @brief Prepares the serializer for writing new data by clearing existing data.
	 * 
	 * This method initializes the `MemoryWriter` with a fresh `Bytes` array.
	 * @note Should be called before any use!
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject")
	virtual void Prepare();

public:
	
	/**
	 * @brief Serializes a 32-bit integer.
	 * 
	 * @param InInteger The integer value to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeInt(UPARAM(DisplayName="Value") int32 InInteger);

	/**
	 * @brief Serializes a 64-bit integer.
	 * 
	 * @param InBigInt The 64-bit integer value to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeBigInt(UPARAM(DisplayName="Value") int64 InBigInt);

	/**
	 * @brief Serializes a floating-point number.
	 * 
	 * @param InFloat The float value to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeFloat(UPARAM(DisplayName="Value") float InFloat);

	/**
	 * @brief Serializes a double-precision floating-point number.
	 * 
	 * @param InDouble The double value to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeDouble(UPARAM(DisplayName="Value") double InDouble);

	/**
	 * @brief Serializes a boolean value.
	 * 
	 * @param InBool The boolean value to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeBool(UPARAM(DisplayName="Value") bool InBool);

	/**
	 * @brief Serializes a single byte.
	 * 
	 * @param InByte The byte value to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeByte(UPARAM(DisplayName="Value") uint8 InByte);

	/**
	 * @brief Serializes a 3D vector (FVector).
	 * 
	 * @param InVector The FVector to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeVector(UPARAM(DisplayName="Value") FVector InVector);

	/**
	 * @brief Serializes a 3D integer vector (FIntVector).
	 * 
	 * @param InVector The FIntVector to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeIntVector(UPARAM(DisplayName="Value") FIntVector InVector);

	/**
	 * @brief Serializes a 2D vector (FVector2D).
	 * 
	 * @param InVector The FVector2D to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeVector2D(UPARAM(DisplayName="Value") FVector2D InVector);

	/**
	 * @brief Serializes a 2D integer point (FIntPoint).
	 * 
	 * @param InPoint The FIntPoint to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializePoint(UPARAM(DisplayName="Value") FIntPoint InPoint);

	/**
	 * @brief Serializes a rotation (FRotator).
	 * 
	 * @param InRotator The FRotator to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeRotator(UPARAM(DisplayName="Value") FRotator InRotator);

	/**
	 * @brief Serializes a transform (FTransform).
	 * 
	 * @param InTransform The FTransform to serialize.
	 */
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeTransform(UPARAM(DisplayName="Value") FTransform InTransform);

	/**
	* @brief Serializes a string (FString).
	* 
	* @param InString The FString to serialize.
	*/
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeString(UPARAM(DisplayName="Value") FString InString);

	/**
	* @brief Serializes a object (UObject).
	* 
	* @param InObject The UObject to serialize.
	*/
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeObject(UPARAM(DisplayName="Value") UObject* InObject);

	/**
	* @brief Serializes a array of objects (TArray<UObject*>).
	* 
	* @param InObjects The Array of UObjects to serialize.
	*/
	UFUNCTION(BlueprintCallable, Category="USerializerObject|Serialization")
	virtual void SerializeObjects(UPARAM(DisplayName="Value") const TArray<UObject*>& InObjects);
};
