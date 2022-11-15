#pragma once

#include "CoreMinimal.h"
#include <string>
#include <vector>
#include <cstddef>

class APTOSSDK_API MathHelper
{
public:
    MathHelper();
    ~MathHelper();

    static std::string FStringToStdString(FString fstring);
    static FString StdStringToFString(std::string stdstring);
    static uint8_t GetBytes(uint16_t value, int index);
    static std::string BytesToHex(uint8_t* _array, int _size);
    static std::string BytesToHex(std::byte* _array, int _size);
    static std::vector<uint8_t> HexToBytes(const std::string& hex);
    static std::vector<std::byte> StringToBytes(std::string string);
    static std::vector<std::byte> UInt64ToBytes(uint64 integer);
    static std::vector<std::byte> UInt8ToBytes(uint8 integer);
    static bool HasHexPrefix(std::string& value);
    static bool IsHex(std::string& value);
    static void Label(const char* _title);
    static void PrintBytes(std::vector<uint8_t> bytes, const char* _title);
    static void PrintBytes(std::vector<std::byte> bytes, const char* _title);
	static void PrintBytes(uint8_t* bytes, int size, const char* _title);
	static void PrintBytes(std::byte* bytes, int size, const char* _title);
    static void PrintSpace();
    static void PrintLine();
    static void Sha3Digest(const std::string _string, std::string* _outHash, std::vector<uint8_t>& _outBytes);
    static std::vector<uint8_t> StdByteVectorToUInt8Vector(std::vector<std::byte> bytes);
    static std::vector<std::byte> UInt8VectorToStdByteVector(std::vector<uint8_t> bytes);
    static std::vector<uint8_t> UInt8PtrToUInt8Vector(uint8_t* bytes, int size);
    static std::vector<std::byte> UInt8PtrToStdByteVector(uint8_t* bytes, int size);
    static std::vector<std::byte> StdBytePtrToStdByteVector(std::byte* bytes, int size);
    static std::vector<uint8_t> StdBytePtrToUInt8Vector(std::byte* bytes, int size);
	
};
