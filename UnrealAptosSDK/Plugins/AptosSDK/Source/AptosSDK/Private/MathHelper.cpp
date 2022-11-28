#include "MathHelper.h"
#include <codecvt>
#include <sstream>
#include <iomanip>
#include "HashLibrary/sha3.h"

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

void MathHelper::PrintBytes(uint8_t* bytes, int size, const char* _title)
{
	FString log = FString("[ ");
	for (int i = 0; i < size; i++)
	{
		log.Append(FString::FromInt(bytes[i]));
		if (i < size - 1) log.Append(", ");
	}
	log.Append(" ]");

	UE_LOG(LogTemp, Warning, TEXT(" "));
	UE_LOG(LogTemp, Warning, TEXT("===================================================================================================="));
	UE_LOG(LogTemp, Warning, TEXT("%s (%d)"), *FString(_title), size);
	UE_LOG(LogTemp, Warning, TEXT("===================================================================================================="));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *log);
	UE_LOG(LogTemp, Warning, TEXT(" "));
}

std::vector<uint8_t> MathHelper::StringToBytes(const std::string _string)
{
	const unsigned int size = _string.size();

	std::byte* bytes = new std::byte[size];
	std::memcpy(bytes, _string.data(), size);

	std::vector<uint8_t> vctr;
	for (unsigned int i = 0; i < size; i++) vctr.push_back(std::to_integer<uint8_t>(bytes[i]));

	return vctr;
}

std::string MathHelper::BytesToString(uint8_t* _array, int _size)
{
	std::ostringstream convert;
	for (int i = 0; i < _size; i++)
	{
		convert << (int)_array[i];
	}
	std::string str = convert.str();
	return str;
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
		c = value[i];
		isHex = ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));

		if (!isHex) return false;
	}
	return true;
}

void MathHelper::ApplyHexPrefix(std::string& value)
{
	if (!HasHexPrefix(value))
	{
		value = std::string("0x") + value;
	}
}

std::string MathHelper::BytesToHex(uint8_t* _array, int _size)
{
	std::stringstream buffer; buffer << std::hex << std::setfill('0');
	for (int i = 0; i < _size; i++)
	{
		buffer << std::setw(2) << static_cast<unsigned>(_array[i]);
	}
	std::string hex = buffer.str();
	ApplyHexPrefix(hex);
	return hex;
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

std::vector<uint8_t> MathHelper::UInt64ToBytes(uint64 integer)
{
	uint64 i = integer;
	uint8_t b[sizeof(uint64)];
	(uint64&)b = i;

	std::vector<uint8_t> vctr;
	for (int v = 0; v < sizeof(b) / sizeof(b[0]); v++)
	{
		std::byte byte = std::byte(b[v]);
		vctr.push_back(std::to_integer<uint8_t>(byte));
	}

	return vctr;
}
std::vector<uint8_t> MathHelper::UInt8ToBytes(uint8 integer)
{
	uint8 i = integer;
	uint8_t b[sizeof(uint8)];
	(uint8&)b = i;

	std::vector<uint8_t> vctr;
	for (int v = 0; v < sizeof(b) / sizeof(b[0]); v++)
	{
		std::byte byte = std::byte(b[v]);
		vctr.push_back(std::to_integer<uint8_t>(byte));
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

TArray<uint8_t> MathHelper::UInt8VectorToTArray(std::vector<uint8_t>& _vector)
{
	TArray<uint8_t> tArray;
	tArray.Append(&_vector[0], _vector.size());
	return tArray;
}

void MathHelper::HexChar(unsigned char c, unsigned char& hex1, unsigned char& hex2)
{
	hex1 = c / 16;
	hex2 = c % 16;
	hex1 += hex1 <= 9 ? '0' : 'a' - 10;
	hex2 += hex2 <= 9 ? '0' : 'a' - 10;
}

std::string MathHelper::UrlEncode(std::string s)
{
	const char* str = s.c_str();
	std::vector<char> v(s.size());
	v.clear();
	for (size_t i = 0, l = s.size(); i < l; i++)
	{
		char c = str[i];
		if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '-' || c == '_' || c == '.' || c == '!' || c == '~' || c == ':' || c == '*' || c == '\'' || c == '(' || c == ')')
		{
			v.push_back(c);
		}
		else if (c == ' ')
		{
			v.push_back('+');
		}
		else
		{
			v.push_back('%');
			unsigned char d1, d2;
			HexChar(c, d1, d2);
			v.push_back(d1);
			v.push_back(d2);
		}
	}

	return std::string(v.cbegin(), v.cend());
}

uint64_t MathHelper::GetExpireTimestamp(int _defaultTxnExpSecFromNow)
{
	FDateTime now = FDateTime::Now();
	FTimespan span = FTimespan::FromSeconds(_defaultTxnExpSecFromNow);
	now += span;
	return now.ToUnixTimestamp();
}

void MathHelper::Sha3Digest(const std::vector<uint8_t> _inBytes, std::string* _outHash, std::vector<uint8_t>& _outBytes)
{
	SHA3 sha3(SHA3::Bits256);
	sha3.add(_inBytes.data(), _inBytes.size());
	std::string sha3hash = sha3.getHash();

	*_outHash = sha3hash;
	_outBytes = HexToBytes(sha3hash);
}