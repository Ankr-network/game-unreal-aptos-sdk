#include "LibraryManager.h"
#include <codecvt>
#include <sstream>
#include <iomanip>
#include "MathHelper.h"

#define crypto_sign_BYTES 64U
#define crypto_sign_SEEDBYTES 32U
#define crypto_sign_PUBLICKEYBYTES 32U
#define crypto_sign_SECRETKEYBYTES (32U + 32U)
#define crypto_hash_sha256_BYTES 32U
#define MAX_MSG_LEN 1024

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

	crypto_hash_sha256_func = reinterpret_cast<crypto_hash_sha256_function>(reinterpret_cast<void*>(GetProcAddress(LibSodiumDynamicLibraryHandle, "crypto_hash_sha256")));
	if (!crypto_hash_sha256_func)
	{
		UE_LOG(LogTemp, Fatal, TEXT("crypto_hash_sha256_func() can not be loaded."));
		return;
	}

	int result = (*sodium_init_func)();
	UE_LOG(LogTemp, Warning, TEXT("sodium_init_func() result: %d"), result);

	isInitialized = result == 0;


	FString dllPath = *FPaths::ProjectPluginsDir() + FString("AptosSDK/Source/AptosSDK/Private/Windows/Libraries/SerialSignClassLibrary.dll");
	bool exists = FPaths::FileExists(dllPath);

	if (exists)
	{
		HNDL = FPlatformProcess::GetDllHandle(*dllPath);
		if (!HNDL)
		{
			UE_LOG(LogTemp, Warning, TEXT("HNDL could not be loaded."));
			return;
		}

		AssignCallbackFunc = (AssignCallbackFunction)FPlatformProcess::GetDllExport(HNDL, *FString("AssignCallback"));
		if (AssignCallbackFunc == NULL)
		{
			UE_LOG(LogTemp, Fatal, TEXT("AssignCallbackFunc() can not be loaded."));
			return;
		}

		AssignCallbackFunc([](const char* message)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(message));
			});

		ConstructPayloadFunc = (ConstructPayloadFunction)FPlatformProcess::GetDllExport(HNDL, *FString("ConstructPayload"));
		if (ConstructPayloadFunc == NULL)
		{
			UE_LOG(LogTemp, Fatal, TEXT("ConstructPayloadFunc() can not be loaded."));
			return;
		}

		GetPayloadSizeFunc = (GetPayloadSizeFunction)FPlatformProcess::GetDllExport(HNDL, *FString("GetPayloadSize"));
		if (ConstructPayloadFunc == NULL)
		{
			UE_LOG(LogTemp, Fatal, TEXT("GetPayloadSizeFunc() can not be loaded."));
			return;
		}
	}
} 

std::vector<std::byte> LibraryManager::construct_payload(const char* _function, const char** _type_arguments, int _type_arguments_size, const char** _arguments, int _arguments_size)
{
	uint8_t* payload			 = ConstructPayloadFunc(_function, _type_arguments, _type_arguments_size, _arguments, _arguments_size);
	int		 size			     = GetPayloadSizeFunc  (_function, _type_arguments, _type_arguments_size, _arguments, _arguments_size);
	std::vector<std::byte> bytes = MathHelper::UInt8PtrToStdByteVector(payload, size);
	return bytes;
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
	
	*_sk = MathHelper::BytesToHex(sk, sklen);
	*_pk = MathHelper::BytesToHex(pk, pklen);
	
	UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_keypair() generated successfully - sk: (%d Bytes) %s | pk: (%d Bytes) %s"), result, sklen, *FString((*_sk).c_str()), pklen, *FString((*_pk).c_str()));
}

void LibraryManager::crypto_sign_keypair(std::vector<uint8_t>& _sk, std::vector<uint8_t>& _pk)
{
	uint8_t sk[crypto_sign_SECRETKEYBYTES];
	uint8_t pk[crypto_sign_PUBLICKEYBYTES];
	int result = crypto_sign_keypair_func(pk, sk);
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_keypair() failed to generate keypair."), result);
		return;
	}

	_sk.insert(_sk.begin(), std::begin(sk), std::end(sk));
	_pk.insert(_pk.begin(), std::begin(pk), std::end(pk));

	MathHelper::PrintBytes(_sk, "Secret Key");
	MathHelper::PrintBytes(_pk, "Public Key");
	//UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_keypair() generated successfully - sk: (%d Bytes) %s | pk: (%d Bytes) %s"), result, sklen, *FString((*_sk).c_str()), pklen, *FString((*_pk).c_str()));
}

std::string LibraryManager::crypto_sign(const std::string& _m, const std::string& _sk)
{
	std::vector<uint8_t> skvtr = MathHelper::HexToBytes(_sk);
	uint8_t sk[crypto_sign_SECRETKEYBYTES];      // secret key
	for (int i = 0; i < skvtr.size(); ++i) sk[i] = skvtr.at(i);
	if (sizeof(sk) / sizeof(sk[0]) != crypto_sign_SECRETKEYBYTES) throw "LibraryManager - crypto_sign() - incorrect secret-key with length in parameter.";

	uint8_t m[MAX_MSG_LEN + crypto_sign_BYTES];  // message
	memset(m, '\0', MAX_MSG_LEN);
	unsigned long long mlen = snprintf((char*)m, MAX_MSG_LEN, "%s", _m.c_str());
	
	uint8_t sm[MAX_MSG_LEN + crypto_sign_BYTES]; // signed message
	unsigned long long smlen;

	int result = crypto_sign_func(sm, &smlen, m, mlen, sk); 
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_func() failed to sign the message with secret-key."), result);
		return std::string("");
	}
	UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_func() signed the message successfully - sk: (%d) %s | m: (%d) %s |=> sm: (%d) %s"), result, sizeof(sk) / sizeof(sk[0]), *FString(MathHelper::BytesToHex(sk, sizeof(sk) / sizeof(sk[0])).c_str()), mlen, *FString(MathHelper::BytesToHex(m, mlen).c_str()), smlen, *FString(MathHelper::BytesToHex(sm, smlen).c_str()));

	return MathHelper::BytesToHex(sm, smlen);
}

std::string LibraryManager::crypto_sign_open(const std::string& _sm, const std::string& _pk)
{
	std::vector<uint8_t> pkvtr = MathHelper::HexToBytes(_pk);
	uint8_t pk[crypto_sign_PUBLICKEYBYTES];      // public key
	for (int i = 0; i < pkvtr.size(); ++i) pk[i] = pkvtr.at(i);
	if (sizeof(pk) / sizeof(pk[0]) != crypto_sign_PUBLICKEYBYTES) throw "LibraryManager - crypto_sign_open() - incorrect public-key with length in parameter.";

	std::vector<uint8_t> smvtr = MathHelper::HexToBytes(_sm);
	unsigned long long smlen = smvtr.size();
	uint8_t sm[MAX_MSG_LEN + crypto_sign_BYTES]; // signed message
	for (int i = 0; i < smlen; ++i) sm[i] = smvtr.at(i);
	
	uint8_t m[MAX_MSG_LEN + crypto_sign_BYTES];  // message
	unsigned long long mlen;

	int result = crypto_sign_open_func(m, &mlen, sm, smlen, pk);
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_open_func() failed to verify the message."), result);
		return std::string("");
	}
	UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_open_func() - m: (%d) %s"), result, mlen, *FString(MathHelper::BytesToHex(m, mlen).c_str()));
	
	return MathHelper::BytesToHex(m, mlen);
}

std::string LibraryManager::crypto_sign_detached(const std::string& _m, const std::string& _sk)
{
	std::vector<uint8_t> skvtr = MathHelper::HexToBytes(_sk);
	uint8_t sk[crypto_sign_SECRETKEYBYTES];      // secret key
	for (int i = 0; i < skvtr.size(); ++i) sk[i] = skvtr.at(i);
	if (sizeof(sk) / sizeof(sk[0]) != crypto_sign_SECRETKEYBYTES) throw "LibraryManager - crypto_sign_detached() - incorrect secret-key with length in parameter.";

	uint8_t m[MAX_MSG_LEN + crypto_sign_BYTES];  // message
	memset(m, '\0', MAX_MSG_LEN);
	unsigned long long mlen = snprintf((char*)m, MAX_MSG_LEN, "%s", _m.c_str());

	uint8_t sg[crypto_sign_BYTES]; // signed message
	unsigned long long sglen;

	int result = crypto_sign_detached_func(sg, &sglen, m, mlen, sk);
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_detached() failed to sign the message with secret-key."), result);
		return std::string("");
	}
	UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_detached() signed the message successfully - sk: (%d) %s | m: (%d) %s |=> sg: (%d) %s"), result, sizeof(sk) / sizeof(sk[0]), *FString(MathHelper::BytesToHex(sk, sizeof(sk) / sizeof(sk[0])).c_str()), mlen, *FString(MathHelper::BytesToHex(m, mlen).c_str()), sglen, *FString(MathHelper::BytesToHex(sg, sglen).c_str()));

	return MathHelper::BytesToHex(sg, sglen);
}

std::string LibraryManager::crypto_sign_detached(const std::vector<uint8_t> _m, const std::vector<uint8_t> _sk)
{
	uint8_t sk[crypto_sign_SECRETKEYBYTES];      // secret key
	for (int i = 0; i < _sk.size(); ++i) sk[i] = _sk.at(i);
	if (sizeof(sk) / sizeof(sk[0]) != crypto_sign_SECRETKEYBYTES) throw "LibraryManager - crypto_sign_detached() - incorrect secret-key with length in parameter.";

	uint8_t sg[crypto_sign_BYTES]; // signed message
	unsigned long long sglen;

	int result = crypto_sign_detached_func(sg, &sglen, _m.data(), _m.size(), _sk.data());
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_detached() failed to sign the message with secret-key."), result);
		return std::string("");
	}
	//UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_detached() signed the message successfully - sk: (%d) %s | m: (%d) %s |=> sg: (%d) %s"), result, _sk.size(), *FString(MathHelper::BytesToHex(_sk.data(), _sk.size()).c_str()), _m.size(), *FString(MathHelper::BytesToHex(_m.data(), _m.size()).c_str()), sglen, *FString(MathHelper::BytesToHex(sg, sglen).c_str()));

	return MathHelper::BytesToHex(sg, sglen);
}

std::string LibraryManager::crypto_sign_verify_detached(const std::string& _sg, const std::string& _sm, const std::string& _pk)
{
	std::vector<uint8_t> sgvtr = MathHelper::HexToBytes(_sg);
	uint8_t sg[crypto_sign_SECRETKEYBYTES];      // secret key
	for (int i = 0; i < sgvtr.size(); ++i) sg[i] = sgvtr.at(i);
	if (sizeof(sg) / sizeof(sg[0]) != crypto_sign_SECRETKEYBYTES) throw "LibraryManager - crypto_sign_verify_detached() - incorrect public-key with length in parameter.";

	std::vector<uint8_t> pkvtr = MathHelper::HexToBytes(_pk);
	uint8_t pk[crypto_sign_PUBLICKEYBYTES];      // secret key
	for (int i = 0; i < pkvtr.size(); ++i) pk[i] = pkvtr.at(i);
	if (sizeof(pk) / sizeof(pk[0]) != crypto_sign_PUBLICKEYBYTES) throw "LibraryManager - crypto_sign_verify_detached() - incorrect public-key with length in parameter.";

	std::vector<uint8_t> smvtr = MathHelper::HexToBytes(_sm);
	unsigned long long smlen = smvtr.size();
	uint8_t sm[MAX_MSG_LEN + crypto_sign_BYTES]; // signed message
	for (int i = 0; i < smlen; ++i) sm[i] = smvtr.at(i);

	int result = crypto_sign_verify_detached_func(sg, sm, smlen, pk);
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_verify_detached() failed to verify the message."), result);
		return std::string("");
	}
	UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_verify_detached() - sm: (%d) %s"), result, smlen, *FString(MathHelper::BytesToHex(sm, smlen).c_str()));

	return MathHelper::BytesToHex(sm, smlen);
}

void LibraryManager::crypto_sign_ed25519_sk_to_pk(std::string* _pk, std::string _sk)
{ 
	std::vector<uint8_t> skvtr = MathHelper::HexToBytes(_sk);
	uint8_t sk[crypto_sign_SECRETKEYBYTES];      // secret key
	for (int i = 0; i < skvtr.size(); ++i) sk[i] = skvtr.at(i);
	if (sizeof(sk) / sizeof(sk[0]) != crypto_sign_SECRETKEYBYTES) throw "LibraryManager - crypto_sign_ed25519_sk_to_pk() - incorrect secret-key with length in parameter.";

	uint8_t pk[crypto_sign_PUBLICKEYBYTES];
	int result = crypto_sign_ed25519_sk_to_pk_func(pk, sk);
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_ed25519_sk_to_pk() failed to generate keypair."), result);
		return;
	}

	int pklen = sizeof(pk) / sizeof(pk[0]);
	*_pk = MathHelper::BytesToHex(pk, pklen);

	UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_sign_ed25519_sk_to_pk() generated successfully - pk: (%d Bytes) %s"), result, pklen, *FString((*_pk).c_str()));
}

void LibraryManager::crypto_hash_sha256(const std::string& _m, std::string* _h)
{
	uint8_t m[MAX_MSG_LEN + crypto_hash_sha256_BYTES];  // message
	memset(m, '\0', MAX_MSG_LEN);
	unsigned long long mlen = snprintf((char*)m, MAX_MSG_LEN, "%s", _m.c_str());

	uint8_t h[crypto_hash_sha256_BYTES];

	int result = crypto_hash_sha256_func(h, m, mlen);
	if (result != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_hash_sha256() failed to generate hash."), result);
		return;
	}

	int hlen = sizeof(h) / sizeof(h[0]);
	*_h = MathHelper::BytesToHex(h, hlen);

	UE_LOG(LogTemp, Warning, TEXT("LibraryManager - %d crypto_hash_sha256() generated successfully - hash: (%d Bytes) %s"), result, hlen, *FString((*_h).c_str()));
}

void LibraryManager::Unload()
{
	if (LibSodiumDynamicLibraryHandle)
	{
		isInitialized = false;

		FPlatformProcess::FreeDllHandle(LibSodiumDynamicLibraryHandle);
		LibSodiumDynamicLibraryHandle = nullptr;
	}
	if (HNDL)
	{
		AssignCallbackFunc   = NULL;
		ConstructPayloadFunc = NULL;
		GetPayloadSizeFunc   = NULL;
		FPlatformProcess::FreeDllHandle(HNDL);
		HNDL = nullptr;
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