#include "MathHelper.h"
#include <codecvt>
#include <sstream>
#include <iomanip>
#include "sha3.h"

MathHelper::MathHelper(){}
MathHelper::~MathHelper(){}

std::string MathHelper::FStringToStdString(FString _string)
{
	return std::string(TCHAR_TO_UTF8(*_string));
}
FString MathHelper::StdStringToFString(std::string _string)
{
	return FString(_string.c_str());
}

uint8_t MathHelper::GetBytes(uint16_t value, int index)
{
	return index ? (uint8_t)((value & 0xff00) >> 8) : (uint8_t)(value & 0x00ff);
}

void MathHelper::PrintBytes(uint8_t* bytes, int size, const char* _title)
{
	FString log = FString("Bytes { ");
	for (int i = 0; i < size; i++)
	{
		uint8_t byte = bytes[i];
		log.Append(FString::FromInt(byte));

		if (i != size - 1) log.Append(", ");

	}
	log.Append(" }");
	Label(_title);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *log);
	PrintSpace();
}

void MathHelper::PrintBytes(std::byte* bytes, int size, const char* _title)
{
	FString log = FString("Bytes { ");
	for (int i = 0; i < size; i++)
	{
		uint8_t byte = std::to_integer<int>(bytes[i]);
		log.Append(FString::FromInt(byte));

		if (i != size - 1) log.Append(", ");

	}
	log.Append(" }");
	Label(_title);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *log);
	PrintSpace();
}

void MathHelper::PrintBytes(std::vector<uint8_t> bytes, const char* _title)
{
	FString log = FString("Bytes { ");
	for (int i = 0; i < bytes.size(); i++)
	{
		uint8_t byte = bytes[i];
		log.Append(FString::FromInt(byte));

		if (i != bytes.size() - 1) log.Append(", ");

	}
	log.Append(" }");
	Label(_title);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *log);
	PrintSpace();
}

void MathHelper::PrintBytes(std::vector<std::byte> bytes, const char* _title)
{
	FString log = FString("Bytes { ");
	for (int i = 0; i < bytes.size(); i++)
	{
		std::byte byte = bytes[i];
		log.Append(FString::FromInt(std::to_integer<int>(byte)));

		if (i != bytes.size() - 1) log.Append(", ");

	}
	log.Append(" }");
	Label(_title);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *log);
	PrintSpace();
}

void MathHelper::PrintSpace()
{
	UE_LOG(LogTemp, Warning, TEXT(" "));
}

void MathHelper::PrintLine()
{
	UE_LOG(LogTemp, Warning, TEXT("===================================================================================================="));
}

void MathHelper::Label(const char* _title)
{
	PrintSpace();
	PrintLine();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(_title));
	PrintLine();
}

std::string MathHelper::BytesToHex(uint8_t* _array, int _size)
{
	std::stringstream buffer; buffer << std::hex << std::setfill('0');
	for (int i = 0; i < _size; i++)
	{
		buffer << std::setw(2) << static_cast<unsigned>(_array[i]);
	}
	std::string string = buffer.str();
	return string;
}
std::string MathHelper::BytesToHex(std::byte* _array, int _size)
{
	std::stringstream buffer; buffer << std::hex << std::setfill('0');
	for (int i = 0; i < _size; i++)
	{
		buffer << std::setw(2) << static_cast<unsigned>(_array[i]);
	}
	std::string string = buffer.str();

	PrintBytes(_array, _size, "BytesToHex");
	UE_LOG(LogTemp, Warning, TEXT("Hex: %s"), *FString(string.c_str()));

	return string;
}

std::vector<uint8_t> MathHelper::HexToBytes(const std::string& hex)
{
	std::string string = std::string(hex.c_str());
	if (HasHexPrefix(string)) string.erase(0, 2);
	
	std::vector<uint8_t> bytes;
	for (unsigned int i = 0; i < string.length(); i += 2)
	{
		std::string byteString = string.substr(i, 2);
		uint8_t byte = (uint8_t)strtol(byteString.c_str(), NULL, 16);
		bytes.push_back(byte);
	}
	return bytes;
}
std::vector<std::byte> MathHelper::StringToBytes(const std::string _string)
{
	const unsigned int size = _string.size();

	std::byte* bytes = new std::byte[size];
	std::memcpy(bytes, _string.data(), size);

	std::vector<std::byte> vctr;
	for (unsigned int i = 0; i < size; i++) vctr.push_back(bytes[i]);

	return vctr;
}

std::vector<std::byte> MathHelper::UInt64ToBytes(uint64 integer)
{
	uint64 i = integer;
	uint8_t b[sizeof(uint64)];
	(uint64&)b = i;

	std::vector<std::byte> vctr;
	for (int v = 0; v < sizeof(b) / sizeof(b[0]); v++)
	{
		std::byte byte = std::byte(b[v]);
		vctr.push_back(byte);
	}

	return vctr;
}
std::vector<std::byte> MathHelper::UInt8ToBytes(uint8 integer)
{
	uint8 i = integer;
	uint8_t b[sizeof(uint8)];
	(uint8&)b = i;

	std::vector<std::byte> vctr;
	for (int v = 0; v < sizeof(b) / sizeof(b[0]); v++)
	{
		std::byte byte = std::byte(b[v]);
		vctr.push_back(byte);
	}

	return vctr;
}

bool MathHelper::HasHexPrefix(std::string& value)
{
	return value.substr(0, 2).compare("0x") == 0;
}
bool MathHelper::IsHex(std::string& value)
{
	bool isHex;
	char c;
	for (int i = 0; i < value.size(); i++)
	{
		c     = value[i];
		isHex = ((c >= '0' && c <= '9') ||
				 (c >= 'a' && c <= 'f') ||
				 (c >= 'A' && c <= 'F'));

		if (!isHex) return false;
	}
	return true;
}

void MathHelper::Sha3Digest(const std::string _string, std::string* _outHash, std::vector<uint8_t>& _outBytes)
{
	const std::vector<std::byte> bytes = StringToBytes(_string);

	SHA3 sha3(SHA3::Bits256);
	sha3.add(bytes.data(), bytes.size());
	std::string sha3hash = sha3.getHash();

	*_outHash = sha3hash;
	_outBytes = HexToBytes(sha3hash);
}

std::vector<uint8_t> MathHelper::StdByteVectorToUInt8Vector(std::vector<std::byte> bytes)
{
	std::vector<uint8_t> vctr;
	for (int i = 0; i < bytes.size(); i++)
	{
		vctr.push_back(std::to_integer<uint8_t>(bytes.at(i)));
	}
	return vctr;
}

std::vector<std::byte> MathHelper::UInt8VectorToStdByteVector(std::vector<uint8_t> bytes)
{
	std::vector<std::byte> vctr;
	for (int i = 0; i < bytes.size(); i++)
	{
		vctr.push_back(std::byte(bytes.at(i)));
	}
	return vctr;
}

std::vector<uint8_t> MathHelper::UInt8PtrToUInt8Vector(uint8_t* bytes, int size)
{
	std::vector<uint8_t> vctr;
	for (int i = 0; i < size; i++)
	{
		vctr.push_back(bytes[i]);
	}
	return vctr;
}

std::vector<std::byte> MathHelper::UInt8PtrToStdByteVector(uint8_t* bytes, int size)
{
	std::vector<std::byte> vctr;
	for (int i = 0; i < size; i++)
	{
		vctr.push_back(std::byte(bytes[i]));
	}
	return vctr;
}

std::vector<std::byte> MathHelper::StdBytePtrToStdByteVector(std::byte* bytes, int size)
{
	std::vector<std::byte> vctr;
	for (int i = 0; i < size; i++)
	{
		vctr.push_back(bytes[i]);
	}
	return vctr;
}

std::vector<uint8_t> MathHelper::StdBytePtrToUInt8Vector(std::byte* bytes, int size)
{
	std::vector<uint8_t> vctr;
	for (int i = 0; i < size; i++)
	{
		vctr.push_back(std::to_integer<uint8_t>(bytes[i]));
	}
	return vctr;
}

