#include "GeneralService.h"
#include "PayloadBuilder.h"
#include "MathHelper.h"

UGeneralService::UGeneralService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {  }

void UGeneralService::GetLedgerInfo(const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/");
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("GeneralService - GetLedgerInfo: %s"), *content);

			FIndexResponse ledger;
			FJsonObjectConverter::JsonObjectStringToUStruct(content, &ledger);

			callback.ExecuteIfBound(content, FString::FromInt(ledger.chain_id));
		}, _callback, false);
}