#include "EventsService.h"
#include "PayloadBuilder.h"
#include "MathHelper.h"

UEventsService::UEventsService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {  }

void UEventsService::GetEventsByCreationNumber(FString _address, FString _creation_number, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/events/").Append(_creation_number);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("EventsService - GetEventsByCreationNumber: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}

void UEventsService::GetEventsByEventHandle(FString _address, FString _event_handle, FString _field_name, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/events/").Append(_event_handle).Append("/").Append(_field_name);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("EventsService - GetEventsByEventHandle: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}