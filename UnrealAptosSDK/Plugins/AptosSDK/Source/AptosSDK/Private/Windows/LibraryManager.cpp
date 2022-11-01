#include "LibraryManager.h"
#include <codecvt>
#include <sstream>
#include <iomanip>

#define crypto_sign_BYTES 64U
#define crypto_sign_SEEDBYTES 32U
#define crypto_sign_PUBLICKEYBYTES 32U
#define crypto_sign_SECRETKEYBYTES (32U + 32U)

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

	isInitialized = true;
}

std::string LibraryManager::crypto_sign_keypair(std::string* _secretKey)
{
	unsigned char publicKeyBytesArray[crypto_sign_PUBLICKEYBYTES];
	unsigned char secretKeyBytesArray[crypto_sign_SECRETKEYBYTES];
	crypto_sign_keypair_func(publicKeyBytesArray, secretKeyBytesArray);
	*_secretKey = std::string((char*)secretKeyBytesArray, sizeof secretKeyBytesArray);

	return std::string((char*)publicKeyBytesArray, sizeof publicKeyBytesArray);
}

std::string LibraryManager::crypto_sign(const std::string& _message, const std::string& _secretKey)
{
	if (_secretKey.size() != crypto_sign_SECRETKEYBYTES) throw "incorrect secret-key length";

	const size_t messageLength = _message.size();
	
	std::vector<unsigned char> signedMessageBytesArray(crypto_sign_BYTES + messageLength);
	unsigned long long signedMessageLength;

	for (int i = 0; i < messageLength; ++i) signedMessageBytesArray.push_back(_message.at(i));
	
	crypto_sign_func(signedMessageBytesArray.data(), &signedMessageLength, signedMessageBytesArray.data(), messageLength, (const unsigned char*)_secretKey.c_str());

	return std::string((char*)signedMessageBytesArray.data(), signedMessageLength);
}

std::string LibraryManager::crypto_sign_open(const std::string& _signedMessage, const std::string& _publicKey)
{
	if (_publicKey.size() != crypto_sign_PUBLICKEYBYTES) throw "incorrect public-key length";

	const size_t signedMessageLength = _signedMessage.size();
	std::vector<unsigned char> m(signedMessageLength);
	unsigned long long messageLength;

	for (int i = 0; i < signedMessageLength; ++i) m.push_back(_signedMessage.at(i));

	int result = crypto_sign_open_func(m.data(), &messageLength, m.data(), signedMessageLength, (const unsigned char*)_publicKey.c_str());
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("crypto_sign_open_func() ciphertext fails verification with result: %d"), result);
		return std::string("");
	}

	return std::string((char*)m.data(), messageLength);
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

std::string LibraryManager::UnsignedCharArrayToHexString(unsigned char* _array, int _size)
{
	std::stringstream buffer;
	for (int i = 0; i < _size; i++)
	{
		buffer << std::hex << std::setfill('0');
		buffer << std::setw(2) << static_cast<unsigned>(_array[i]);
	}
	return buffer.str();;
}
