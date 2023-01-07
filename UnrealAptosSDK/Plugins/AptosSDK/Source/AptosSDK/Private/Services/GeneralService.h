#pragma once

#include "AptosClientBase.h"
#include "AptosSchemas.h"
#include "GeneralService.generated.h"

/// GeneralService class is used to get general information about Aptos.
UCLASS(Blueprintable, BlueprintType)
class APTOSSDK_API UGeneralService : public UAptosClientBase
{
	GENERATED_UCLASS_BODY()

	public:

		/// Gets the latest ledger information, including data such as chain ID, role type, ledger versions, epoch, etc.
		///
		/// @param _callback A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetLedgerInfo(const FAptosCallCompleteDynamicDelegate& _callback);
};