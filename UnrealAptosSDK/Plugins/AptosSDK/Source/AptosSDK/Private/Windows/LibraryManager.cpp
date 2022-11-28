#include "LibraryManager.h"
#include "MathHelper.h"
#include "CryptoConstants.h"


void LibraryManager::Load()
{
	isInitialized = false;

	const FString SodiumDynamicLibraryPath = *FPaths::ProjectPluginsDir() + FString("AptosSDK/Source/AptosSDK/Private/Windows/Libraries/libsodium.dll");

	LibSodiumDynamicLibraryHandle = LoadLibrary(GetWString(SodiumDynamicLibraryPath).c_str());
	if (LibSodiumDynamicLibraryHandle == nullptr)
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

	crypto_sign_seed_keypair_func = reinterpret_cast<crypto_sign_seed_keypair_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_sign_keypair")));
	if (!crypto_sign_seed_keypair_func)
	{
		UE_LOG(LogTemp, Fatal, TEXT("crypto_sign_seed_keypair_func() can not be loaded."));
		return;
	}

	crypto_sign_keypair_func = reinterpret_cast<crypto_sign_keypair_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_sign_keypair")));
	if (!crypto_sign_keypair_func)
	{
		UE_LOG(LogTemp, Fatal, TEXT("crypto_sign_keypair_func() can not be loaded."));
		return;
	}

	crypto_sign_func = reinterpret_cast<crypto_sign_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_sign")));
	if (!crypto_sign_func)
	{
		UE_LOG(LogTemp, Fatal, TEXT("crypto_sign_func() can not be loaded."));
		return;
	}

	crypto_sign_open_func = reinterpret_cast<crypto_sign_open_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_sign_open")));
	if (!crypto_sign_open_func)
	{
		UE_LOG(LogTemp, Fatal, TEXT("crypto_sign_open_func() can not be loaded."));
		return;
	}

	crypto_sign_detached_func = reinterpret_cast<crypto_sign_detached_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_sign_detached")));
	if (!crypto_sign_detached_func)
	{
		UE_LOG(LogTemp, Fatal, TEXT("crypto_sign_detached_func() can not be loaded."));
		return;
	}
	
	crypto_sign_verify_detached_func = reinterpret_cast<crypto_sign_verify_detached_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_sign_verify_detached")));
	if (!crypto_sign_verify_detached_func)
	{
		UE_LOG(LogTemp, Fatal, TEXT("crypto_sign_verify_detached_func() can not be loaded."));
		return;
	}
	
	crypto_sign_ed25519_sk_to_pk_func = reinterpret_cast<crypto_sign_ed25519_sk_to_pk_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_sign_ed25519_sk_to_pk")));
	if (!crypto_sign_ed25519_sk_to_pk_func)
	{
		UE_LOG(LogTemp, Fatal, TEXT("crypto_sign_ed25519_sk_to_pk_func() can not be loaded."));
		return;
	}

	crypto_sign_ed25519_sk_to_seed_func = reinterpret_cast<crypto_sign_ed25519_sk_to_seed_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_sign_ed25519_sk_to_pk")));
	if (!crypto_sign_ed25519_sk_to_seed_func)
	{
		UE_LOG(LogTemp, Fatal, TEXT("crypto_sign_ed25519_sk_to_seed_func() can not be loaded."));
		return;
	}

	int result = (*sodium_init_func)();
	UE_LOG(LogTemp, Warning, TEXT("sodium_init_func() result: %d"), result);

	isInitialized = result == 0;
} 

void LibraryManager::crypto_sign_seed_keypair(std::vector<uint8_t>& _out_sk, std::vector<uint8_t>& _out_pk, std::vector<uint8_t>& _in_seed)
{
	uint8_t sk[crypto_sign_SECRETKEYBYTES];
	uint8_t pk[crypto_sign_PUBLICKEYBYTES];
	
	int result = crypto_sign_seed_keypair_func(pk, sk, _in_seed.data());
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_seed_keypair() failed to generate keypair."), result);
		return;
	}

	_out_sk.insert(_out_sk.begin(), std::begin(sk), std::end(sk));
	_out_pk.insert(_out_pk.begin(), std::begin(pk), std::end(pk));
}

void LibraryManager::crypto_sign_keypair(std::vector<uint8_t>& _out_sk, std::vector<uint8_t>& _out_pk)
{
	uint8_t sk[crypto_sign_SECRETKEYBYTES];
	uint8_t pk[crypto_sign_PUBLICKEYBYTES];
	int result = crypto_sign_keypair_func(pk, sk);
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_keypair() failed to generate keypair."), result);
		return;
	}

	_out_sk.insert(_out_sk.begin(), std::begin(sk), std::end(sk));
	_out_pk.insert(_out_pk.begin(), std::begin(pk), std::end(pk));
}

void LibraryManager::crypto_sign(const std::vector<uint8_t>& _in_m, const std::vector<uint8_t>& _in_sk, std::vector<uint8_t>& _out_sm)
{
	if (_in_sk.size() != crypto_sign_SECRETKEYBYTES) throw "LibraryManager - crypto_sign() - incorrect secret-key with length in parameter.";

	uint8_t sm[MAX_MSG_LEN + crypto_sign_BYTES];
	unsigned long long smlen;
	int result = crypto_sign_func(sm, &smlen, _in_m.data(), _in_m.size(), _in_sk.data());
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_func() failed to sign the message with secret-key."), result);
		return;
	}

	_out_sm.insert(_out_sm.begin(), std::begin(sm), std::end(sm));
}

void LibraryManager::crypto_sign_open(const std::vector<uint8_t>& _in_sm, const std::vector<uint8_t>& _in_pk, std::vector<uint8_t>& _out_m)
{
	if (_in_pk.size() != crypto_sign_PUBLICKEYBYTES) throw "LibraryManager - crypto_sign_open() - incorrect public-key with length in parameter.";

	uint8_t m[MAX_MSG_LEN + crypto_sign_BYTES];
	unsigned long long mlen;
	int result = crypto_sign_open_func(m, &mlen, _in_sm.data(), _in_sm.size(), _in_pk.data());
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_open_func() failed to verify the message."), result);
		return;
	}

	_out_m.insert(_out_m.begin(), std::begin(m), std::end(m));
}

void LibraryManager::crypto_sign_detached(const std::vector<uint8_t>& _in_m, const std::vector<uint8_t>& _in_sk, std::vector<uint8_t>& _out_sg)
{
	if (_in_sk.size() != crypto_sign_SECRETKEYBYTES) throw "LibraryManager - crypto_sign_detached() - incorrect secret-key with length in parameter.";

	uint8_t sg[crypto_sign_BYTES];
	unsigned long long sglen;

	int result = crypto_sign_detached_func(sg, &sglen, _in_m.data(), _in_m.size(), _in_sk.data());
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_detached() failed to sign the message with secret-key."), result);
		return;
	}
	
	_out_sg.insert(_out_sg.begin(), std::begin(sg), std::end(sg));
}

void LibraryManager::crypto_sign_verify_detached(const std::vector<uint8_t>& _in_sg, const std::vector<uint8_t>& _in_m, const std::vector<uint8_t>& _in_pk, bool& v)
{
	if (_in_pk.size() != crypto_sign_PUBLICKEYBYTES) throw "LibraryManager - crypto_sign_verify_detached() - incorrect public-key with length in parameter.";

	int result = crypto_sign_verify_detached_func(_in_sg.data(), _in_m.data(), _in_m.size(), _in_pk.data());
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_verify_detached() failed to verify the message."), result);
		return;
	}
	
	v = result == 0;
}
void LibraryManager::crypto_sign_ed25519_sk_to_seed(std::vector<uint8_t>& _out_seed,  std::vector<uint8_t>& _in_sk)
{
	if (_in_sk.size() != crypto_sign_SECRETKEYBYTES) throw "LibraryManager - crypto_sign_ed25519_sk_to_pk() - incorrect secret-key with length in parameter.";

	uint8_t seed[crypto_sign_SEEDBYTES];
	int result = crypto_sign_ed25519_sk_to_seed_func(seed, _in_sk.data());
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_ed25519_sk_to_seed() failed to generate keypair."), result);
		return;
	}

	_out_seed.insert(_out_seed.begin(), std::begin(seed), std::end(seed));
}
void LibraryManager::crypto_sign_ed25519_sk_to_pk(std::vector<uint8_t>& _out_pk, const std::vector<uint8_t>& _in_sk)
{
	if (_in_sk.size() != crypto_sign_SECRETKEYBYTES) throw "LibraryManager - crypto_sign_ed25519_sk_to_pk() - incorrect secret-key with length in parameter.";

	uint8_t pk[crypto_sign_PUBLICKEYBYTES];
	int result = crypto_sign_ed25519_sk_to_pk_func(pk, _in_sk.data());
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_ed25519_sk_to_pk() failed to generate keypair."), result);
		return;
	}

	_out_pk.insert(_out_pk.begin(), std::begin(pk), std::end(pk));
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