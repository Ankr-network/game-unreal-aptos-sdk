#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "GenericPlatform/GenericPlatform.h"
#include <JsonObjectConverter.h>
#include <string>
#include "AnkrDelegates.h"
#include "AptosSchemas.generated.h"

USTRUCT(BlueprintType)
struct FAccountData
{
	GENERATED_BODY()

	UPROPERTY() FString sequence_number;
	UPROPERTY() FString authentication_key;

	static FString ToJson(FAccountData _item)
	{
		FString json;
		FJsonObjectConverter::UStructToJsonObjectString(_item, json);
		return json;
	}

	static FAccountData FromJson(FString json)
	{
		FAccountData object{};
		FJsonObjectConverter::JsonObjectStringToUStruct(json, &object, 0, 0);
		return object;
	}
};

UCLASS()
class APTOSSDK_API UAptosSchemas : public UUserDefinedStruct
{
	GENERATED_BODY()
};
