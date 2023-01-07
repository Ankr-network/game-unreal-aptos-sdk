#include "AccountsService.h"
#include "MathHelper.h"

UAccountsService::UAccountsService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {  }

void UAccountsService::GetAccount(FString _address, FString _ledger_version, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("AccountsService - GetAccount: %s"), *content);

			FAccountData accountData;
			FJsonObjectConverter::JsonObjectStringToUStruct(content, &accountData, 0, 0);

			callback.ExecuteIfBound(content, accountData.sequence_number);
		}, _callback, false);
}

void UAccountsService::GetAccountResources(FString _address, FString _ledger_version, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/resources");
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("AccountsService - GetAccountResources: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}

void UAccountsService::GetAccountModules(FString _address, FString _ledger_version, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/modules");
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("AccountsService - GetAccountModules: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}

void UAccountsService::GetAccountResource(FString _address, FString _resource_type, FString _ledger_version, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString resource_type = FString(MathHelper::UrlEncode(MathHelper::FStringToStdString(*_resource_type)).c_str());

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/resource/").Append(resource_type);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("AccountsService - GetAccountResource: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}

void UAccountsService::GetAccountModule(FString _address, FString _module_name, FString _ledger_version, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/module/").Append(_module_name);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("AccountsService - GetAccountModule: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}