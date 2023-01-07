#pragma once

#include "AptosClientBase.h"
#include "AptosSchemas.h"
#include "AccountsService.generated.h"

/// AccountsService class is used to get information about Aptos accounts, resources and modules.
UCLASS(Blueprintable, BlueprintType)
class APTOSSDK_API UAccountsService : public UAptosClientBase
{
	GENERATED_UCLASS_BODY()

public:

	/// Gets the account data containing an authentication key and a sequence number. 
	///
	/// @param _address        The address for which the account data to be received.
	/// @param _ledger_version A version for the ledger or the latest ledger version is retrieved if no version is specified.
	/// @param _callback       A callback to be executed when the _callback is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccount(FString _address, FString _ledger_version, const FAptosCallCompleteDynamicDelegate& _callback);

	/// Retrieves all account resources for a given account at a specific ledger version.
	///
	/// @param _address        The address for which the account data to be received.
	/// @param _ledger_version A version for the ledger or the latest ledger version is retrieved if no version is specified.
	/// @param _limit          Max number of account resources to retrieve.
	/// @param _start          Cursor specifying where to start for pagination.
	/// @param _callback       A callback to be executed when the _callback is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountResources(FString _address, FString _ledger_version, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback);

	/// Retrieves all account modules' bytecode for a given account at a specific ledger version.
	///
	/// @param _address        The address for which the account data to be received.
	/// @param _ledger_version A version for the ledger or the latest ledger version is retrieved if no version is specified.
	/// @param _limit          Max number of account modules to retrieve.
	/// @param _start          Cursor specifying where to start for pagination.
	/// @param _callback       A callback to be executed when the _callback is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountModules(FString _address, FString _ledger_version, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback);

	/// Gets an individual resource from a given account at a specific ledger version.
	///
	/// @param _address        The address for which the account data to be received.
	/// @param _resource_type  Name of the struct to retrieve.
	/// @param _ledger_version A version for the ledger or the latest ledger version is retrieved if no version is specified.
	/// @param _callback       A callback to be executed when the _callback is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountResource(FString _address, FString _resource_type, FString _ledger_version, const FAptosCallCompleteDynamicDelegate& _callback);

	/// Retrieves an individual module from a given account at a specific ledger version.
	///
	/// @param _address        The address for which the account data to be received.
	/// @param _module_name    Name of the module to retrieve.
	/// @param _ledger_version A version for the ledger or the latest ledger version is retrieved if no version is specified.
	/// @param _callback       A callback to be executed when the _callback is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountModule(FString _address, FString _module_name, FString _ledger_version, const FAptosCallCompleteDynamicDelegate& _callback);
};