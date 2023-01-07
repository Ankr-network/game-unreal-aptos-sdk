#include "BlocksService.h"
#include "PayloadBuilder.h"
#include "MathHelper.h"

UBlocksService::UBlocksService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {  }

void UBlocksService::GetBlocksByHeight(int _block_height, bool _with_transactions, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/blocks/by_height/").Append(FString::FromInt(_block_height));
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("BlocksService - GetBlocksByHeight: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}

void UBlocksService::GetBlocksByVersion(int _version, bool _with_transactions, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/blocks/by_version/").Append(FString::FromInt(_version));
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("BlocksService - GetBlocksByVersion: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}