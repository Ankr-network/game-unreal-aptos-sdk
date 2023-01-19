#pragma once

#include "CoreMinimal.h"
#include <string>
#include <vector>
#include <cstddef>
#include "Math/BigInt.h"
#include "Math/Int128.h"

class APTOSSDK_API MathHelper
{
public:
    MathHelper();
    ~MathHelper();

    static std::string FStringToStdString(FString fstring);
    static FString StdStringToFString(std::string stdstring);
	static void PrintBytes(uint8_t* bytes, int size, const char* _title);
    static std::vector<uint8_t> StringToBytes(std::string string);
    static std::string BytesToString(uint8_t* _array, int _size);
	static bool HasHexPrefix(std::string& value);
	static bool IsHex(std::string& value);
    static void ApplyHexPrefix(std::string& value);
    static std::string BytesToHex(uint8_t* _array, int _size);
    static std::vector<uint8_t> HexToBytes(const std::string& hex);
    static std::vector<uint8_t> UInt64ToBytes(FUInt128 integer);
    static std::vector<uint8_t> UInt64ToBytes(uint64 integer);
    static std::vector<uint8_t> UInt32ToBytes(uint32 integer);
    static std::vector<uint8_t> UInt16ToBytes(uint16 integer);
    static std::vector<uint8_t> UInt8ToBytes(uint8 integer);
	static std::vector<uint8_t> UInt8PtrToUInt8Vector(uint8_t* bytes, int size);
    static TArray<uint8_t> UInt8VectorToTArray(std::vector<uint8_t>& _vector);
    static void HexChar(unsigned char c, unsigned char& hex1, unsigned char& hex2);
    static std::string UrlEncode(std::string s);
    static uint64_t GetExpireTimestamp(int _defaultTxnExpSecFromNow);
    static void Sha3Digest(const std::vector<uint8_t> _inBytes, std::string* _outHash, std::vector<uint8_t>& _outBytes);
};
