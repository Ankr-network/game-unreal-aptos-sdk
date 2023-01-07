#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include <JsonObjectConverter.h>
#include "MathHelper.h"
#include "../Private/Windows/LibraryManager.h"
#include "CryptoConstants.h"
#include "PayloadBuilder.h"
#include "AptosSchemas.generated.h"

USTRUCT(BlueprintType)
struct FArgument
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString Item;
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") TArray<FString> Array;
};

USTRUCT(BlueprintType)
struct FTransactionPayload
{
	GENERATED_BODY()

	FString type;								   // string
	FString function;							   // string
	TArray<TSharedPtr<FJsonValue>> type_arguments; // array[string]
	TArray<TSharedPtr<FJsonValue>> arguments;	   // array[string]
	TSharedPtr<FJsonObject> builder;

	FTransactionPayload()
	{
		builder = UPayloadBuilder::GetBuilder();
	}

	void Update()
	{
		builder->SetStringField("function",		 function);
		builder->SetArrayField("type_arguments", type_arguments);
		builder->SetArrayField("arguments",		 arguments);
		builder->SetStringField("type",			"entry_function_payload");
	}

	TSharedPtr<FJsonObject> ToJsonObject()
	{
		return builder;
	}
};

USTRUCT(BlueprintType)
struct FAccountData
{
	GENERATED_BODY()

	UPROPERTY() FString sequence_number;    // string<uint64>
	UPROPERTY() FString authentication_key; // string<hex>
};

USTRUCT(BlueprintType)
struct FTransactionSignature
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString type;		  // string
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString public_key; // string<hex>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString signature;  // string <hex>

	TSharedPtr<FJsonObject> ToJsonObject()
	{
		TSharedPtr<FJsonObject> builder = UPayloadBuilder::GetBuilder();
		builder->SetStringField("type", type);
		builder->SetStringField("public_key", public_key);
		builder->SetStringField("signature", signature);
		return builder;
	}
};

USTRUCT(BlueprintType)
struct FAptosError
{
	GENERATED_BODY()

	UPROPERTY() FString message;	// string
	UPROPERTY() FString error_code; // string
	UPROPERTY() int vm_error_code;  // integer
};

USTRUCT(BlueprintType)
struct FEncodeSubmissionRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="APTOS SDK") FString sender;					   // string<hex>
	UPROPERTY(BlueprintReadWrite, Category="APTOS SDK") FString sequence_number;		   // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category="APTOS SDK") FString max_gas_amount;			   // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category="APTOS SDK") FString gas_unit_price;			   // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category="APTOS SDK") FString expiration_timestamp_secs; // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category="APTOS SDK") FTransactionPayload payload;	   // object
	UPROPERTY(BlueprintReadWrite, Category="APTOS SDK") TArray<FString> secondary_signers; // array[string]<hex>

	TSharedPtr<FJsonObject> ToJsonObject()
	{
		TSharedPtr<FJsonObject> builder = UPayloadBuilder::GetBuilder();
		builder->SetStringField("sender",					 sender);
		builder->SetStringField("sequence_number",			 sequence_number);
		builder->SetStringField("max_gas_amount",			 max_gas_amount);
		builder->SetStringField("gas_unit_price",			 gas_unit_price);
		builder->SetStringField("expiration_timestamp_secs", expiration_timestamp_secs);
		builder->SetObjectField("payload",					 payload.ToJsonObject());
		
		if(!secondary_signers.IsEmpty())
		{
			TArray<TSharedPtr<FJsonValue>> signers;
			for (int i = 0; i < signers.Num(); i++)
			{
				UPayloadBuilder::AddArrayItem(signers, secondary_signers[i]);
			}
			builder->SetArrayField("secondary_signers", signers);
		}
		
		return builder;
	}
};

USTRUCT(BlueprintType)
struct FGasEstimation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") int deprioritized_gas_estimate; // integer
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") int gas_estimate;				  // integer
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") int prioritized_gas_estimate;	  // integer
};

USTRUCT(BlueprintType)
struct FIndexResponse
{
	GENERATED_BODY()

	UPROPERTY() int chain_id;				   // integer
	UPROPERTY() FString epoch;				   // string<uint64>
	UPROPERTY() FString ledger_version;		   // string<uint64>
	UPROPERTY() FString oldest_ledger_version; // string<uint64>
	UPROPERTY() FString ledger_timestamp;	   // string<uint64>
	UPROPERTY() FString node_role;			   // string
	UPROPERTY() FString oldest_block_height;   // string<uint64>
	UPROPERTY() FString block_height;		   // string<uint64>
	UPROPERTY() FString git_hash;		       // string
};

USTRUCT(BlueprintType)
struct FPendingTransaction
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString hash;					     // string
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString sender;					 // string<hex>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString sequence_number;		     // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString max_gas_amount;			 // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString gas_unit_price;			 // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString expiration_timestamp_secs; // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FTransactionPayload payload;		 // object
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FAccountData signature;			 // object
};

USTRUCT(BlueprintType)
struct FSubmitTransactionRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString sender;					 // string<hex>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString sequence_number;		     // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString max_gas_amount;			 // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString gas_unit_price;			 // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString expiration_timestamp_secs; // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FTransactionPayload payload;	     // object
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FTransactionSignature signature;	     // object

	TSharedPtr<FJsonObject> ToJsonObject()
	{
		TSharedPtr<FJsonObject> builder = UPayloadBuilder::GetBuilder();
		builder->SetStringField("sender", sender);
		builder->SetStringField("sequence_number", sequence_number);
		builder->SetStringField("max_gas_amount", max_gas_amount);
		builder->SetStringField("gas_unit_price", gas_unit_price);
		builder->SetStringField("expiration_timestamp_secs", expiration_timestamp_secs);
		builder->SetObjectField("payload", payload.ToJsonObject());
		builder->SetObjectField("signature", signature.ToJsonObject());
		return builder;
	}
};

USTRUCT(BlueprintType)
struct FTransaction
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString type;					     // string
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString hash;					     // string
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString sender;					 // string<hex>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString sequence_number;		     // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString max_gas_amount;			 // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString gas_unit_price;			 // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString expiration_timestamp_secs; // string<uint64>
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FTransactionPayload payload;	     // object
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FAccountData signature;			 // object
};

USTRUCT(BlueprintType)
struct FAptosAccount
{
	GENERATED_BODY()

private:

    std::vector<uint8_t> seed;
	std::vector<uint8_t> privateKey;
	std::vector<uint8_t> publicKey;
	
public:

	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString Address;
	UPROPERTY(BlueprintReadWrite, Category = "APTOS SDK") FString PublicKey;
	UPROPERTY(BlueprintReadOnly, Category  = "APTOS SDK") FString Seed;

	FAptosAccount() { }

	void CreateKeyPair()
	{
		LibraryManager::GetInstance().crypto_sign_keypair(privateKey, publicKey);
		LibraryManager::GetInstance().crypto_sign_ed25519_sk_to_seed(seed, privateKey);

		Seed	  = FString(MathHelper::BytesToHex(seed.data(), seed.size()).c_str());
		Address   = FString(GetAddress().c_str());
		PublicKey = FString(MathHelper::BytesToHex(publicKey.data(), publicKey.size()).c_str());
	}

	void CreateSeedKeyPair(std::vector<uint8_t> _seed)
	{
		seed = _seed;
		LibraryManager::GetInstance().crypto_sign_seed_keypair(privateKey, publicKey, seed);

		Seed      = FString(MathHelper::BytesToHex(seed.data(), seed.size()).c_str());
		Address   = FString(GetAddress().c_str());
		PublicKey = FString(MathHelper::BytesToHex(publicKey.data(), publicKey.size()).c_str());
	}

	void CreateFromPrivateKey(std::vector<uint8_t> _sk)
	{
		auto start = _sk.begin();
		auto end   = _sk.begin() + 32;
		std::vector<uint8_t> _seed(start, end);
		CreateSeedKeyPair(_seed);
	}
	
	void ExtractFromPrivateKey(std::vector<uint8_t> _sk)
	{
		privateKey = _sk;
		LibraryManager::GetInstance().crypto_sign_ed25519_sk_to_pk(publicKey, privateKey);
		LibraryManager::GetInstance().crypto_sign_ed25519_sk_to_seed(seed, privateKey);

		Seed      = FString(MathHelper::BytesToHex(seed.data(), seed.size()).c_str());
		Address   = FString(GetAddress().c_str());
		PublicKey = FString(MathHelper::BytesToHex(publicKey.data(), publicKey.size()).c_str());
	}

	std::string GetAddress()
	{
		std::vector<uint8_t> temporary = publicKey;
		temporary.push_back(0x00); // Single Signature Scheme

		std::string hash;
		std::vector<uint8_t> bytes;
		MathHelper::Sha3Digest(temporary, &hash, bytes);
		MathHelper::ApplyHexPrefix(hash);
		return hash;
	}

	std::vector<uint8_t> Sign(std::vector<uint8_t> message)
	{
		std::vector<uint8_t> signature;
		LibraryManager::GetInstance().crypto_sign_detached(message, privateKey, signature);
		return signature;
	}
};

UCLASS()
class APTOSSDK_API UAptosSchemas : public UUserDefinedStruct
{
	GENERATED_BODY()
};
