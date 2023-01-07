#pragma once

#include "AptosClientBase.h"
#include "AptosSchemas.h"
#include "BlocksService.generated.h"

/// BlocksService class is used to get the transactions in a block and its corresponding block information.
UCLASS(Blueprintable, BlueprintType)
class APTOSSDK_API UBlocksService : public UAptosClientBase
{
	GENERATED_UCLASS_BODY()

	public:

		/// Allows you to get the transactions in a block and the corresponding block information.
		///
		/// @param _block_height      Block height to lookup. Starts at 0.
		/// @param _with_transactions If set to true, include all transactions in the block.
		/// @param _callback          A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetBlocksByHeight(int _block_height, bool _with_transactions, const FAptosCallCompleteDynamicDelegate& _callback);

		///  Allows you to get the transactions in a block and the corresponding block information given a version in the block.
		///
		/// @param _version           Ledger version to lookup block information for.
		/// @param _with_transactions If set to true, include all transactions in the block.
		/// @param _callback          A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetBlocksByVersion(int _version, bool _with_transactions, const FAptosCallCompleteDynamicDelegate& _callback);
};