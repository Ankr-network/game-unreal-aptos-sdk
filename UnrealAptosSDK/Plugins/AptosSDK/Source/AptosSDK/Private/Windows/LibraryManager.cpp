#include "LibraryManager.h"
#include <codecvt>
#include <sstream>
#include <iomanip>

#define crypto_sign_BYTES 64U
#define crypto_sign_SEEDBYTES 32U
#define crypto_sign_PUBLICKEYBYTES 32U
#define crypto_sign_SECRETKEYBYTES (32U + 32U)

#define MAX_MSG_LEN 1024



void LibraryManager::Load()
{
	isInitialized = false;

	const FString SodiumDynamicLibraryPath = *FPaths::ProjectPluginsDir() + FString("AptosSDK/Source/AptosSDK/Private/Windows/Libraries/libsodium.dll");

LibSodiumDynamicLibraryHandle = LoadLibrary(GetWString(SodiumDynamicLibraryPath).c_str());

if (LibSodiumDynamicLibraryHandle != nullptr)
{
	UE_LOG(LogTemp, Warning, TEXT("libsodium.dll loaded successfully!"));
}
else
{
	UE_LOG(LogTemp, Fatal, TEXT("libsodium.dll failed to load!"));
	return;
}

sodium_init_func = reinterpret_cast<sodium_init_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "sodium_init")));
if (!sodium_init_func)
{
	UE_LOG(LogTemp, Fatal, TEXT("sodium_init_func() can not be loaded."));
	return;
}
else
{
	UE_LOG(LogTemp, Warning, TEXT("sodium_init_func() is loaded."));
}

crypto_sign_keypair_func = reinterpret_cast<crypto_sign_keypair_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_sign_keypair")));
if (!crypto_sign_keypair_func)
{
	UE_LOG(LogTemp, Fatal, TEXT("crypto_sign_keypair_func() can not be loaded."));
	return;
}
else
{
	UE_LOG(LogTemp, Warning, TEXT("crypto_sign_keypair_func() is loaded."));
}

crypto_sign_func = reinterpret_cast<crypto_sign_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_sign")));
if (!crypto_sign_func)
{
	UE_LOG(LogTemp, Fatal, TEXT("crypto_sign_func() can not be loaded."));
	return;
}
else
{
	UE_LOG(LogTemp, Warning, TEXT("crypto_sign_func() is loaded."));
}

crypto_sign_open_func = reinterpret_cast<crypto_sign_open_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_sign_open")));
if (!crypto_sign_open_func)
{
	UE_LOG(LogTemp, Fatal, TEXT("crypto_sign_open_func() can not be loaded."));
	return;
}
else
{
	UE_LOG(LogTemp, Warning, TEXT("crypto_sign_open_func() is loaded."));
}

int result = (*sodium_init_func)();
UE_LOG(LogTemp, Warning, TEXT("sodium_init_func() result: %d"), result);

isInitialized = result == 0;
}

void LibraryManager::crypto_sign_keypair(std::string* _sk, std::string* _pk)
{
	uint8_t sk[crypto_sign_SECRETKEYBYTES];
	uint8_t pk[crypto_sign_PUBLICKEYBYTES];
	int result = crypto_sign_keypair_func(pk, sk);
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_keypair() failed to generate keypair."), result);
		return;
	}

	int sklen = sizeof(sk) / sizeof(sk[0]);
	int pklen = sizeof(pk) / sizeof(pk[0]);
	
	*_sk = BytesToHex(sk, sklen);
	*_pk = BytesToHex(pk, pklen);
	
	UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_keypair() generated successfully - sk: (%d Bytes) %s | pk: (%d Bytes) %s"), result, sklen, *FString((*_sk).c_str()), pklen, *FString((*_pk).c_str()));
}

std::string LibraryManager::crypto_sign(const std::string& _m, const std::string& _sk)
{
	// <Secret Key>
	std::vector<uint8_t> skvtr = HexToBytes(_sk);
	uint8_t sk[crypto_sign_SECRETKEYBYTES];      // secret key
	for (int i = 0; i < skvtr.size(); ++i) sk[i] = skvtr.at(i);
	if (sizeof(sk) / sizeof(sk[0]) != crypto_sign_SECRETKEYBYTES) throw "LibraryManager - crypto_sign() - incorrect secret-key with length in parameter.";
	// </Secret Key>

	// <Message>
	uint8_t m[MAX_MSG_LEN + crypto_sign_BYTES];  // message
	memset(m, '\0', MAX_MSG_LEN);
	unsigned long long mlen = snprintf((char*)m, MAX_MSG_LEN, "%s", _m.c_str());
	// </Message>
	
	// <Signed Message>
	uint8_t sm[MAX_MSG_LEN + crypto_sign_BYTES]; // signed message
	unsigned long long smlen;
	// </Signed Message>
	int result = crypto_sign_func(sm, &smlen, m, mlen, sk); 
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_func() failed to sign the message with secret-key."), result);
		return std::string("");
	}
	UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_func() signed the message successfully - sk: (%d) %s | m: (%d) %s |=> sm: (%d) %s"), result, sizeof(sk) / sizeof(sk[0]), *FString(BytesToHex(sk, sizeof(sk) / sizeof(sk[0])).c_str()), mlen, *FString(BytesToHex(m, mlen).c_str()), smlen, *FString(BytesToHex(sm, smlen).c_str()));

	return BytesToHex(sm, smlen);
}

std::string LibraryManager::crypto_sign_open(const std::string& _sm, const std::string& _pk)
{
	// <Public Key>
	std::vector<uint8_t> pkvtr = HexToBytes(_pk);
	uint8_t pk[crypto_sign_PUBLICKEYBYTES];      // secret key
	for (int i = 0; i < pkvtr.size(); ++i) pk[i] = pkvtr.at(i);
	if (sizeof(pk) / sizeof(pk[0]) != crypto_sign_PUBLICKEYBYTES) throw "LibraryManager - crypto_sign_open() - incorrect public-key with length in parameter.";
	// </Public Key>

	// <Signed Message>
	std::vector<uint8_t> smvtr = HexToBytes(_sm);
	unsigned long long smlen = smvtr.size();
	uint8_t sm[MAX_MSG_LEN + crypto_sign_BYTES]; // signed message
	for (int i = 0; i < smlen; ++i) sm[i] = smvtr.at(i);
	// </Signed Message>
	
	// Message
	uint8_t m[MAX_MSG_LEN + crypto_sign_BYTES];  // message
	unsigned long long mlen;
	// </Message>

	int result = crypto_sign_open_func(m, &mlen, sm, smlen, pk);
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_open_func() failed to verify the message."), result);
		return std::string("");
	}
	UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_open_func() - m: (%d) %s"), result, mlen, *FString(BytesToHex(m, mlen).c_str()));
	
	return BytesToHex(m, mlen);
}

void LibraryManager::Unload()
{
	if (LibSodiumDynamicLibraryHandle)
	{
		isInitialized = false;

		FPlatformProcess::FreeDllHandle(LibSodiumDynamicLibraryHandle);
		LibSodiumDynamicLibraryHandle = nullptr;
	}
}

std::string LibraryManager::FStringToStdString(FString fstring)
{
	std::string conversion = std::string(TCHAR_TO_UTF8(*fstring));

	return conversion;
}
FString LibraryManager::StdStringToFString(std::string stdstring)
{
	FString conversion(stdstring.c_str());

	return conversion;
}

std::string LibraryManager::GetString(std::wstring _wstring)
{
	int count = WideCharToMultiByte(CP_UTF8, 0, _wstring.c_str(), _wstring.length(), NULL, 0, NULL, NULL);
	std::string str(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, _wstring.c_str(), -1, &str[0], count, NULL, NULL);
	return str;
}
std::wstring LibraryManager::GetWString(FString input)
{
	std::string raw = std::string(TCHAR_TO_UTF8(*input));
	int count = MultiByteToWideChar(CP_UTF8, 0, raw.c_str(), raw.length(), NULL, 0);
	std::wstring wstr(count, 0);
	MultiByteToWideChar(CP_UTF8, 0, raw.c_str(), raw.length(), &wstr[0], count);
	return wstr;
}

std::string LibraryManager::BytesToHex(uint8_t* _array, int _size)
{
	std::stringstream buffer;
	for (int i = 0; i < _size; i++)
	{
		buffer << std::hex << std::setfill('0');
		buffer << std::setw(2) << static_cast<unsigned>(_array[i]);
	}
	return buffer.str();;
}

std::vector<uint8_t> LibraryManager::HexToBytes(const std::string& hex)
{
	std::vector<uint8_t> bytes;

	for (unsigned int i = 0; i < hex.length(); i += 2) 
	{
		std::string byteString = hex.substr(i, 2);
		uint8_t byte = (uint8_t)strtol(byteString.c_str(), NULL, 16);
		bytes.push_back(byte);
	}

	return bytes;
}
