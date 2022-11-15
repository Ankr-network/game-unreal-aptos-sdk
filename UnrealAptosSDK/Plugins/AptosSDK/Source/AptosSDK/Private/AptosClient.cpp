#include "AptosClient.h"
#include "PayloadBuilder.h"

#include "MathHelper.h"
#include "LibraryManager.h"
#include "keccak.h"
#include "Sha3.h"

UAptosClient::UAptosClient(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

void UAptosClient::GetAccount(FString _address, FString _qledger_version, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			
			FAccountData accountData;
			FJsonObjectConverter::JsonObjectStringToUStruct(content, &accountData, 0, 0);

			callback.ExecuteIfBound(content, accountData.sequence_number, "", -1, false);

		}, Result, false);
}

void UAptosClient::GetAccountResources(FString _address, FString _qledger_version, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/resources");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetAccountModules(FString _address, FString _qledger_version, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/modules");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetAccountResource(FString _address, FString _resource_type, FString _qledger_version, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/resource/").Append(_resource_type);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetAccountModule(FString _address, FString _module_name, FString _qledger_version, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/module/").Append(_module_name);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetBlocksByHeight(FString _block_height, bool qwith_transactions, FString _ledger_version, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/blocks/by_height/").Append(_block_height);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetBlocksByVersion(FString _version, bool qwith_transactions, FString _ledger_version, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/blocks/by_version/").Append(_version);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetEventsByCreationNumber(FString _address, FString _creation_number, int _qlimit, FString _qstart, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("events/").Append(_creation_number);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetEventsByEventHandle(FString _address, FString _event_handle, FString _field_name, int _qlimit, FString _qstart, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("events/").Append(_event_handle).Append("/").Append(_field_name);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::ShowOpenAPIExplorer(const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/spec");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::CheckBasicNodeHealth(int _qduration_secs, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/-/healthy");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetLedgerInfo(const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);

			FIndexResponse output;
			FJsonObjectConverter::JsonObjectStringToUStruct(content, &output);

			FString json;
			FJsonObjectConverter::UStructToJsonObjectString(output, json);
			callback.ExecuteIfBound(json, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetTableItem(FString _table_handle, FString _qledger_version, FString _bkey_type, FString _bvalue_type, FString _bkey, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/tables").Append(_table_handle).Append("/item");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetTransactions(int _qlimit, FString _qstart, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "POST", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::SubmitTransactions(FString _bsender, FString _bsequence_number, FString _bmax_gas_amount, FString _bgas_unit_price, FString _bexpiration_timestamp_secs,FString _qstart, FSubmitTransactionRequest _submitTransactionRequest, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "POST", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - SubmitTransactions: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetTransactionByHash(FString _txn_hash, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions/by_hash/").Append(_txn_hash);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetTransactionByVersion(FString _txn_version, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions/by_version/").Append(_txn_version);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::GetAccountTransactions(FString _address, int _plimit, FString _pstart, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/transactions");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::SubmitBatchTransactions(FString _bsender, FString _bsequence_number, FString _bmax_gas_amount, FString _bgas_unit_price, FString _bexpiration_timestamp_secs, const FAnkrCallCompleteDynamicDelegate& Result)
{
	//UE_LOG(LogTemp, Warning, TEXT("SubmitTransactions : %s"), *UPayloadBuilder::Build(builder));

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions/batch");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "POST", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::SimulateTransactions(FString _bsender, FString _bsequence_number, FString _bmax_gas_amount, FString _bgas_unit_price, FString _bexpiration_timestamp_secs, const FAnkrCallCompleteDynamicDelegate& Result)
{
	//UE_LOG(LogTemp, Warning, TEXT("SubmitTransactions : %s"), *UPayloadBuilder::Build(builder));

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions/simulate");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "POST", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::EncodeSubmission(FString _bsender, FString _bsequence_number, FString _bmax_gas_amount, FString _bgas_unit_price, FString _bexpiration_timestamp_secs, FString _type, FString _function, TArray<FString> _type_arguments, TArray<FString> _arguments, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions/encode_submission");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "POST", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - EncodeSubmission: %s"), *content);

			callback.ExecuteIfBound(content, "", "" , -1, false);

		}, Result, false);
}

void UAptosClient::EstimateGasPrice(const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/estimate_gas_price");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

		}, Result, false);
}

void UAptosClient::CryptoSignKeyPair(FString& _secretKey, FString& _publicKey)
{
	std::string sk;
	std::string pk;
	LibraryManager::GetInstance().crypto_sign_keypair(&sk, &pk);

	_secretKey = FString(sk.c_str());
	_publicKey = FString(pk.c_str());
}

void UAptosClient::CryptoSign(const FString _message, const FString _secretKey, FString& _outSignedMessage)
{
	std::string sm = LibraryManager::GetInstance().crypto_sign(MathHelper::FStringToStdString(*_message), MathHelper::FStringToStdString(*_secretKey));
	_outSignedMessage = MathHelper::StdStringToFString(sm);
}

void UAptosClient::CryptoSignDetach(const FString _message, const FString _secretKey, FString& _outSignature)
{
	std::string sm = LibraryManager::GetInstance().crypto_sign_detached(MathHelper::FStringToStdString(*_message), MathHelper::FStringToStdString(*_secretKey));
	_outSignature = MathHelper::StdStringToFString(sm);
}

void UAptosClient::CryptoSignEd25519SecretKeyToPublicKey(FString& _publicKey, FString _secretKey)
{
	std::string pk;
	std::string sk = MathHelper::FStringToStdString(*_secretKey);

	LibraryManager::GetInstance().crypto_sign_ed25519_sk_to_pk(&pk, sk);

	_publicKey = FString(pk.c_str());
}

void UAptosClient::CryptoHashSha256(FString _message, FString& _hash)
{
	std::string hash;
	std::string input = MathHelper::FStringToStdString(*_message);

	LibraryManager::GetInstance().crypto_hash_sha256(input, &hash);

	_hash = MathHelper::StdStringToFString(hash);
}

void UAptosClient::RawTransactionTest()
{
	std::string hash;
	std::vector<uint8_t> bytes;
	MathHelper::Sha3Digest(std::string("APTOS::RawTransaction"), &hash, bytes);

	FRawTransaction rawTx;
	rawTx.sender = FString("0xa8583bfca93e862653cac142fd09ff848249180906036978a8ca8e6a8ee55778");
	rawTx.sequence_number = 0;
	rawTx.max_gas_amount = 200000;
	rawTx.gas_unit_price = 100;
	rawTx.expiration_timestamp_secs = 1667905991;
	rawTx.chain_id = 36;

	std::vector<uint8_t> message = rawTx.Serialize();
	bytes.insert(bytes.end(), std::begin(message), std::end(message));
	MathHelper::PrintBytes(bytes, "MessageToSign");

	std::vector<uint8_t> privateKey
	{
		255, 211, 113, 35, 165, 87, 101, 140, 224, 222, 92, 33, 154, 65, 150, 110, 140, 93, 2, 42, 28, 171, 127, 97, 43, 26, 129, 71, 81, 123, 43, 127, 184, 15, 11, 253, 79, 245, 134, 84, 235, 194, 101, 199, 183, 86, 195, 6, 154, 234, 47, 136, 15, 71, 94, 119, 91, 201, 60, 202, 25, 182, 116, 124
	};
	std::string signature = LibraryManager::GetInstance().crypto_sign_detached(bytes, privateKey);
	UE_LOG(LogTemp, Warning, TEXT("signature: %s"), *FString(signature.c_str()));
}