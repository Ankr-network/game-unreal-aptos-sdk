#include "AptosClient.h"
#include "PayloadBuilder.h"
#include "AptosSchemas.h"

UAptosClient::UAptosClient(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) 
{}

void UAptosClient::GetAccount(FString _address, FString _qledger_version, const FAnkrCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			callback.ExecuteIfBound(content, "", "", -1, false);

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

void UAptosClient::SubmitTransactions(FString _bsender, FString _bsequence_number, FString _bmax_gas_amount, FString _bgas_unit_price, FString _bexpiration_timestamp_secs,FString _qstart, const FAnkrCallCompleteDynamicDelegate& Result)
{
	TArray<TSharedPtr<FJsonValue>> type_arguments;
	UPayloadBuilder::AddArrayItem(type_arguments, FString("string"));

	TArray<TSharedPtr<FJsonValue>> arguments;
	UPayloadBuilder::AddArrayItem(arguments, FString(""));

	TSharedPtr<FJsonObject> payload = UPayloadBuilder::GetBuilder();
	payload->SetStringField("type", "entry_function_payload");
	payload->SetStringField("function", "0x1::aptos_coin::transfer");
	payload->SetArrayField("type_arguments", type_arguments);
	payload->SetArrayField("arguments", arguments);

	//UPayloadBuilder::AddNestedArray(payload, type_arguments);
	//UPayloadBuilder::AddNestedArray(payload, arguments);

	TSharedPtr<FJsonObject> builder = UPayloadBuilder::GetBuilder();
	builder->SetStringField("sender", "Hey I am sender");
	builder->SetObjectField("payload", payload);

	TSharedPtr<FJsonObject> signature = UPayloadBuilder::GetBuilder();
	signature->SetStringField("type", "ed25519_signature");
	signature->SetStringField("public_key", "0x00");
	signature->SetStringField("signature", "0x00");

	builder->SetObjectField("signature", signature);
	UE_LOG(LogTemp, Warning, TEXT("SubmitTransactions : %s"), *UPayloadBuilder::Build(builder));

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAnkrCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
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