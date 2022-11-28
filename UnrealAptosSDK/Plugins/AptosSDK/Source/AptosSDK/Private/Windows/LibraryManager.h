#pragma once

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

typedef int(__cdecl* sodium_init_function)				      ();
typedef int(__cdecl* crypto_sign_seed_keypair_function)	      (unsigned char*, unsigned char*, const unsigned char*);
typedef int(__cdecl* crypto_sign_keypair_function)		      (unsigned char*, unsigned char*);
typedef int(__cdecl* crypto_sign_function)				      (unsigned char*, unsigned long long*, const unsigned char*, unsigned long long, const unsigned char*);
typedef int(__cdecl* crypto_sign_open_function)			      (unsigned char*, unsigned long long*, const unsigned char*, unsigned long long, const unsigned char*);
typedef int(__cdecl* crypto_sign_detached_function)		      (unsigned char*, unsigned long long*, const unsigned char*, unsigned long long, const unsigned char*);
typedef int(__cdecl* crypto_sign_verify_detached_function)    (const unsigned char*, const unsigned char*, unsigned long long, const unsigned char*);
typedef int(__cdecl* crypto_sign_ed25519_sk_to_pk_function)   (unsigned char*, const unsigned char*);
typedef int(__cdecl* crypto_sign_ed25519_sk_to_seed_function) (unsigned char*, const unsigned char*);

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
		sodium_init_function				    sodium_init_func					= NULL;
		crypto_sign_seed_keypair_function	    crypto_sign_seed_keypair_func		= NULL;
		crypto_sign_keypair_function		    crypto_sign_keypair_func			= NULL;
		crypto_sign_function				    crypto_sign_func					= NULL;
		crypto_sign_open_function			    crypto_sign_open_func				= NULL;
		crypto_sign_detached_function		    crypto_sign_detached_func			= NULL;
		crypto_sign_verify_detached_function    crypto_sign_verify_detached_func	= NULL;
		crypto_sign_ed25519_sk_to_pk_function   crypto_sign_ed25519_sk_to_pk_func	= NULL;
		crypto_sign_ed25519_sk_to_seed_function crypto_sign_ed25519_sk_to_seed_func = NULL;

		void crypto_sign_seed_keypair	    (std::vector<uint8_t>& _out_sk, std::vector<uint8_t>& _out_pk, std::vector<uint8_t>& _in_seed);
		void crypto_sign_keypair            (std::vector<uint8_t>& _out_sk, std::vector<uint8_t>& _out_pk);
		void crypto_sign                    (const std::vector<uint8_t>& _in_m,  const std::vector<uint8_t>& _in_sk, std::vector<uint8_t>& _out_sm);
		void crypto_sign_open               (const std::vector<uint8_t>& _in_sm, const std::vector<uint8_t>& _in_pk, std::vector<uint8_t>& _out_m);
		void crypto_sign_detached           (const std::vector<uint8_t>& _in_m,  const std::vector<uint8_t>& _in_sk, std::vector<uint8_t>& _out_sg);
		void crypto_sign_verify_detached    (const std::vector<uint8_t>& _in_sg, const std::vector<uint8_t>& _in_m, const std::vector<uint8_t>& _in_pk, bool& out_v);
		void crypto_sign_ed25519_sk_to_pk   (std::vector<uint8_t>& _out_pk, const std::vector<uint8_t>& _in_sk);
		void crypto_sign_ed25519_sk_to_seed (std::vector<uint8_t>& _out_seed,  std::vector<uint8_t>& _in_sk);

		std::string  GetString  (std::wstring _wstring);
		std::wstring GetWString (FString input);

		bool isInitialized;

		void Load();
		void Unload();
};