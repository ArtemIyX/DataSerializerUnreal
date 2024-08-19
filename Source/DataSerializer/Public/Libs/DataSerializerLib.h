// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataSerializerLib.generated.h"

constexpr int32 XEUS_SAVEGAME_FILE_TYPE_TAG = 0x78657573; //XEUS

/**
 * @brief Structure for handling serialization headers in any project.
 * 
 * This structure is used to manage the metadata required for serializing and deserializing objects,
 * including information about the type of the object being serialized.
 */
USTRUCT(Blueprintable, BlueprintType)
struct DATASERIALIZER_API FSerializationHeader
{
	GENERATED_BODY()

public:
	/**
	 * @brief Default constructor for FSerializationHeader.
	 * 
	 * Initializes an instance of the FSerializationHeader with default values.
	 */
	FSerializationHeader();
	/**
	 * @brief Constructor with specified object type.
	 * 
	 * @param ObjectType The class type of the object to be serialized.
	 * This constructor sets the GameClassName based on the provided object type.
	 */
	FSerializationHeader(TSubclassOf<UObject> ObjectType);

	/**
	* @brief Resets the header to its default state.
	* 
	* This method clears the GameClassName and any other stateful data
	* in the FSerializationHeader, preparing it for reuse or ensuring it is in a known clean state.
	*/
	void Empty();

	/**
	 * @brief Reads header data from a memory reader.
	 * 
	 * @param MemoryReader The memory reader from which the header data will be read.
	 * This method populates the FSerializationHeader's members based on the data
	 * read from the provided MemoryReader.
	 */
	void Read(FMemoryReader& MemoryReader);

	/**
	* @brief Writes header data to a memory writer.
	* 
	* @param MemoryWriter The memory writer to which the header data will be written.
	* This method serializes the FSerializationHeader's members and writes them to the
	* provided MemoryWriter.
	*/
	void Write(FMemoryWriter& MemoryWriter);

	/**
	* @brief The class name of the game object being serialized.
	* 
	* This string holds the class name of the UObject being serialized, which can be used to
	* identify or reconstruct the object type during deserialization.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
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
	/**
	 * Writes a byte array to a file on disk.
	 *
	 * This function writes the contents of the provided `InBytes` array to a file specified by `InPath`.
	 * The file will be created if it does not exist, or overwritten if it does.
	 * 
	 * @param InBytes The byte array to be written to the file.
	 * @param InPath The path to the file where the byte array should be written.
	 * @return Returns true if the operation was successful, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Disk")
	static bool WriteBytesToDisk(const TArray<uint8>& InBytes, FString InPath);

	/**
	 * Writes a compressed byte array to a file on disk.
	 *
	 * This function first compresses the provided `InBytes` array and then writes the compressed data
	 * to a file specified by `InPath`. The file will be created if it does not exist, or overwritten if it does.
	 *
	 * @param InBytes The byte array to be compressed and written to the file.
	 * @param InPath The path to the file where the compressed byte array should be written.
	 * @return Returns true if the operation was successful, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Disk")
	static bool WriteBytesToDiskCompressed(const TArray<uint8>& InBytes, FString InPath);

	/**
	 * Reads a byte array from a file on disk.
	 *
	 * This function reads the contents of the file specified by `InPath` into the `OutBytes` array.
	 * The file must exist and be readable for this operation to succeed.
	 *
	 * @param OutBytes The byte array that will be populated with the data read from the file.
	 * @param InPath The path to the file from which the byte array should be read.
	 * @return Returns true if the operation was successful, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Disk")
	static bool ReadBytesFromDisk(TArray<uint8>& OutBytes, FString InPath);

	/**
	 * Reads a compressed byte array from a file on disk and decompresses it.
	 *
	 * This function reads the compressed contents of the file specified by `InPath` into the `OutBytes`
	 * array after decompressing it. The file must exist and be readable for this operation to succeed.
	 *
	 * @param OutBytes The byte array that will be populated with the decompressed data read from the file.
	 * @param InPath The path to the file from which the compressed byte array should be read and decompressed.
	 * @return Returns true if the operation was successful, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Disk")
	static bool ReadCompressedBytesFromDisk(TArray<uint8>& OutBytes, FString InPath);

#pragma endregion

#pragma region Serialize
	/**
	 * Serializes an object into a byte array.
	 *
	 * This function converts the given `InObject` into a byte array and populates `OutBytes` with the serialized data.
	 * The serialization process converts the object into a format that can be easily stored or transmitted.
	 *
	 * @param OutBytes The byte array that will be populated with the serialized object data.
	 * @param InObject The object to be serialized.
	 * @return Returns true if the serialization was successful, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Serialization")
	static bool SerializeObject(TArray<uint8>& OutBytes, UObject* InObject);

	/**
	 * Deserializes a byte array into an object.
	 *
	 * This function converts the byte array `InBytes` into an object of type `UObject` and assigns it to `OutObject`.
	 * The deserialization process reconstructs the object from the byte array.
	 *
	 * @param InBytes The byte array containing the serialized object data.
	 * @param ObjectOuter The outer object for the deserialization process. This can be used to specify an outer context for the deserialized object.
	 * @param OutObject The object that will be populated with the deserialized data.
	 * @return Returns true if the deserialization was successful, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Serialization")
	static bool DeserializeObject(const TArray<uint8>& InBytes, UObject* ObjectOuter, UObject*& OutObject);

	/**
	 * Serializes multiple objects into a byte array.
	 *
	 * This function converts the array of objects `InObjects` into a byte array and populates `OutBytes` with the serialized data.
	 * Each object is serialized in sequence and combined into a single byte array.
	 *
	 * @param OutBytes The byte array that will be populated with the serialized objects data.
	 * @param InObjects The array of objects to be serialized.
	 * @return Returns true if the serialization was successful, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Serialization")
	static bool SerializeObjects(TArray<uint8>& OutBytes, TArray<UObject*> InObjects);

	/**
	 * Deserializes a byte array into multiple objects.
	 *
	 * This function converts the byte array `InBytes` into an array of objects and assigns them to `OutObjects`.
	 * The byte array should contain serialized data for multiple objects in sequence.
	 *
	 * @param InBytes The byte array containing the serialized objects data.
	 * @param InObjectOuter The outer object for the deserialization process. This can be used to specify an outer context for the deserialized objects.
	 * @param OutObjects The array that will be populated with the deserialized objects.
	 * @return Returns true if the deserialization was successful, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Serialization")
	static bool DeSerializeObjects(const TArray<uint8>& InBytes, UObject* InObjectOuter, TArray<UObject*>& OutObjects);
#pragma endregion

#pragma region Utils

	/**
	 * Converts a string into a UTF-8 byte array.
	 *
	 * This function takes a string `InString` and converts it into a byte array using UTF-8 encoding. 
	 * The resulting byte array is stored in `OutBytes`.
	 *
	 * @param InString The string to be converted into a UTF-8 byte array.
	 * @param OutBytes The byte array that will be populated with the UTF-8 encoded data.
	 */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Utils")
	static void GetUtf8Bytes(const FString& InString, TArray<uint8>& OutBytes);

	/**
	 * Converts a UTF-8 byte array back into a string.
	 *
	 * This function takes a byte array `InBytes` encoded in UTF-8 and converts it back into a string.
	 *
	 * @param InBytes The byte array containing UTF-8 encoded data to be converted into a string.
	 * @return Returns the string representation of the UTF-8 encoded byte array.
	 */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Utils")
	static FString Utf8BytesToString(const TArray<uint8>& InBytes);

	/**
	 * Concatenates two byte arrays into one.
	 *
	 * This function takes two byte arrays `InLeftPart` and `InRightPart` and combines them into a single byte array.
	 * The resulting byte array contains the data from `InLeftPart` followed by the data from `InRightPart`.
	 *
	 * @param InLeftPart The first byte array to be concatenated.
	 * @param InRightPart The second byte array to be concatenated.
	 * @return Returns a new byte array that is the concatenation of `InLeftPart` and `InRightPart`.
	 */
	UFUNCTION(BlueprintCallable, Category="UDataSerializerLib|Utils")
	static TArray<uint8> AppendBytes(const TArray<uint8>& InLeftPart, const TArray<uint8>& InRightPart);
#pragma endregion
};
