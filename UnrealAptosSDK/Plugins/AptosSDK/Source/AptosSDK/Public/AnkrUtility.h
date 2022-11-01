#pragma once

#include "CoreMinimal.h"
#include "AnkrUtility.generated.h"

const FString API_DEVELOPMENT_URL		= FString(TEXT("https://fullnode.devnet.aptoslabs.com/v1"));

const FString CONTENT_TYPE_KEY			= FString(TEXT("Content-Type"));
const FString CONTENT_TYPE_VALUE		= FString(TEXT("application/json"));

static FString LastRequest;

UCLASS()
class APTOSSDK_API UAnkrUtility : public UObject
{
	GENERATED_BODY()

public:
	
	static FString GetUrl();
	static FString GetLastRequest();
	static void SetLastRequest(FString _lastRequest);
};