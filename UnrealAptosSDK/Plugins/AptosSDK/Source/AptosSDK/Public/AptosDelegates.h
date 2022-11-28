#pragma once

#include "AptosDelegates.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAptosCallCompleteDynamicDelegate, FString, response, FString, data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FApplicationResume);

UCLASS()
class APTOSSDK_API UAptosDelegates : public UObject
{
	GENERATED_BODY()
};