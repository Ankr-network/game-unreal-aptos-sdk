#pragma once

#define crypto_sign_BYTES						64U
#define crypto_sign_SEEDBYTES					32U
#define crypto_sign_PUBLICKEYBYTES				32U
#define crypto_sign_SECRETKEYBYTES				(32U + 32U)
#define crypto_hash_sha256_BYTES				32U
#define MAX_MSG_LEN								1024