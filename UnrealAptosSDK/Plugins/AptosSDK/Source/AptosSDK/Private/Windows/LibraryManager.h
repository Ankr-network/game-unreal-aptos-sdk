#pragma once

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

typedef int(__cdecl* sodium_init_function)();
typedef int(__cdecl* crypto_sign_keypair_function)(unsigned char*, const unsigned char*);
typedef int(__cdecl* crypto_sign_function)(unsigned char*, unsigned long long*, const unsigned char*, unsigned long long, const unsigned char*);
typedef int(__cdecl* crypto_sign_open_function)(unsigned char*, unsigned long long*, const unsigned char*, unsigned long long, const unsigned char*);

class APTOSSDK_API LibraryManager
{
	public:
		static LibraryManager& GetInstance()
		{
			static LibraryManager INSTANCE;
			return INSTANCE;
		}

	private:
		LibraryManager() {}

	public:
		LibraryManager(LibraryManager const&) = delete;
		void operator = (LibraryManager const&) = delete;

	public:

		HINSTANCE LibSodiumDynamicLibraryHandle; 
		sodium_init_function		 sodium_init_func         = NULL;
		crypto_sign_keypair_function crypto_sign_keypair_func = NULL;
		crypto_sign_function		 crypto_sign_func		  = NULL;
		crypto_sign_open_function    crypto_sign_open_func    = NULL;

		void crypto_sign_keypair(std::string* _sk, std::string* _pk);
		std::string crypto_sign(const std::string& _m, const std::string& _sk);
		std::string crypto_sign_open(const std::string& _sm, const std::string& _pk);

		bool isInitialized;

		void Load();
		void Unload();
		
		std::string GetString(std::wstring _wstring);
		std::wstring GetWString(FString input);
		std::string BytesToHex(uint8_t* _array, int _size);
		std::vector<uint8_t> HexToBytes(const std::string& hex);
		std::string FStringToStdString(FString fstring);
		FString StdStringToFString(std::string stdstring);

};