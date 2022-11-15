#pragma once

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

typedef int(__cdecl* sodium_init_function)				   ();
typedef int(__cdecl* crypto_sign_keypair_function)		   (unsigned char*, const unsigned char*);
typedef int(__cdecl* crypto_sign_function)				   (unsigned char*, unsigned long long*, const unsigned char*, unsigned long long, const unsigned char*);
typedef int(__cdecl* crypto_sign_open_function)			   (unsigned char*, unsigned long long*, const unsigned char*, unsigned long long, const unsigned char*);
typedef int(__cdecl* crypto_sign_detached_function)		   (unsigned char*, unsigned long long*, const unsigned char*, unsigned long long, const unsigned char*);
typedef int(__cdecl* crypto_sign_verify_detached_function) (const unsigned char*, const unsigned char*, unsigned long long, const unsigned char*);
typedef int(__cdecl* crypto_sign_ed25519_sk_to_pk_function)(unsigned char*, const unsigned char*);
typedef int(__cdecl* crypto_hash_sha256_function)		   (unsigned char*, const unsigned char*, unsigned long long);

typedef void(*Log)(const char* message);
using AssignCallbackFunction   = void      (__stdcall*) (Log);
using ConstructPayloadFunction = uint8_t*  (__stdcall*)(const char*, const char**, int, const char**, int);
using GetPayloadSizeFunction   = int	   (__stdcall*)(const char*, const char**, int, const char**, int);

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
		LibraryManager(LibraryManager const&)   = delete;
		void operator = (LibraryManager const&) = delete;

	public:

		HINSTANCE LibSodiumDynamicLibraryHandle; 
		sodium_init_function		  sodium_init_func						    = NULL;
		crypto_sign_keypair_function  crypto_sign_keypair_func				    = NULL;
		crypto_sign_function		  crypto_sign_func						    = NULL;
		crypto_sign_open_function     crypto_sign_open_func					    = NULL;
		crypto_sign_detached_function crypto_sign_detached_func				    = NULL;
		crypto_sign_verify_detached_function crypto_sign_verify_detached_func   = NULL;
		crypto_sign_ed25519_sk_to_pk_function crypto_sign_ed25519_sk_to_pk_func = NULL;
		crypto_hash_sha256_function crypto_hash_sha256_func						= NULL;

		void* HNDL																= NULL;
		AssignCallbackFunction AssignCallbackFunc								= NULL;
		ConstructPayloadFunction ConstructPayloadFunc							= NULL;
		GetPayloadSizeFunction GetPayloadSizeFunc								= NULL;

		void crypto_sign_keypair                (std::string* _sk, std::string* _pk);
		void crypto_sign_keypair				(std::vector<uint8_t>& _sk, std::vector<uint8_t>& _pk);
		std::string crypto_sign                 (const std::string& _m, const std::string& _sk);
		std::string crypto_sign_detached        (const std::string& _m, const std::string& _sk);
		std::string crypto_sign_detached		(const std::vector<uint8_t> _m, const std::vector<uint8_t> _sk);
		std::string crypto_sign_open            (const std::string& _sm, const std::string& _pk);
		std::string crypto_sign_verify_detached (const std::string& _sg, const std::string& _sm, const std::string& _pk);
		void crypto_sign_ed25519_sk_to_pk       (std::string* _pk, std::string _sk);
		void crypto_hash_sha256				    (const std::string& _m, std::string* _h);

		std::vector<std::byte> construct_payload(const char* _function, const char** _type_arguments, int _type_arguments_size, const char** _arguments, int _arguments_size);

		std::string  GetString  (std::wstring _wstring);
		std::wstring GetWString (FString input);

		bool isInitialized;

		void Load();
		void Unload();
};