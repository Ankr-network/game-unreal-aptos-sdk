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

		/// <summary>
		/// The crypto_sign_keypair function randomly generates a secret key and a corresponding public key. 
		/// It puts the secret key into sk and returns the public key. It guarantees that sk has crypto_sign_SECRETKEYBYTES bytes and that pk has crypto_sign_PUBLICKEYBYTES bytes.
		/// </summary>
		/// <param name="sk_string"></param>
		/// <returns></returns>
		std::string crypto_sign_keypair(std::string* sk_string);

		/// <summary>
		/// The crypto_sign function signs a message m using the signer's secret key sk. 
		/// The crypto_sign function returns the resulting signed message sm. The function raises an exception if sk.size() is not crypto_sign_SECRETKEYBYTES.
		/// </summary>
		/// <param name="m_string"></param>
		/// <param name="sk_string"></param>
		/// <returns></returns>
		std::string crypto_sign(const std::string& m_string, const std::string& sk_string);

		/// <summary>
		/// The crypto_sign_open function verifies the signature in sm using the signer's public key pk. The crypto_sign_open function returns the message m.
		//If the signature fails verification, crypto_sign_open raises an exception.The function also raises an exception if pk.size() is not crypto_sign_PUBLICKEYBYTES.
		/// </summary>
		/// <param name="sm_string"></param>
		/// <param name="pk_string"></param>
		/// <returns></returns>
		std::string crypto_sign_open(const std::string& sm_string, const std::string& pk_string);

		bool isInitialized;

		void Load();
		void Unload();
		
		std::string GetString(std::wstring _wstring);
		std::wstring GetWString(FString input);
		std::string UnsignedCharArrayToHexString(unsigned char* _array, int _size);
};