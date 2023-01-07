#pragma once

#include "AptosClientBase.h"
#include "AptosSchemas.h"
#include "../Private/Services/AccountsService.h"
#include "../Private/Services/BlocksService.h"
#include "../Private/Services/EventsService.h"
#include "../Private/Services/GeneralService.h"
#include "../Private/Services/TablesService.h"
#include "../Private/Services/TransactionsService.h"
#include "AptosClient.generated.h"

#define DOXYGEN_SHOULD_SKIP_THIS

/// AptosClient provides services that are used to interact with the Aptos blockchain.
UCLASS(Blueprintable, BlueprintType)
class APTOSSDK_API UAptosClient : public UAptosClientBase
{
	GENERATED_UCLASS_BODY()

public:

//#ifndef DOXYGEN_SHOULD_SKIP_THIS
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AptosSDK")UAccountsService*	  accountsService     = NULL;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AptosSDK")UBlocksService*		  blocksService       = NULL;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AptosSDK")UEventsService*		  eventsService       = NULL;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AptosSDK")UGeneralService*	  generalService      = NULL;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AptosSDK")UTablesService*		  tablesService		  = NULL;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AptosSDK")UTransactionsService* transactionsService = NULL;
//#endif /* DOXYGEN_SHOULD_SKIP_THIS */

	/// Initialize Aptos services for accounts, blocks, events, general, tables and transactions.
	///
	/// The function doesn't require any parameters and returns an Aptos account for test purposes.\n
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void Initialize();

	/// Gets a test Aptos account for a person named Alice.
	///
	/// The function doesn't require any parameters and returns an Aptos account for test purposes.\n
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	FAptosAccount GetAliceAccount();

	/// Gets a test Aptos account for a person named Bob.
	///
	/// The function doesn't require any parameters and returns an Aptos account for test purposes.\n
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	FAptosAccount GetBobAccount();
};