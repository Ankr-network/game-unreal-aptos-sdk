#pragma once

#include "AptosClientBase.h"
#include "AptosSchemas.h"
#include "TablesService.generated.h"

/// TablesService class is used to get the items from tables.
UCLASS(Blueprintable, BlueprintType)
class APTOSSDK_API UTablesService : public UAptosClientBase
{
	GENERATED_UCLASS_BODY()

	public:

		/// Gets a table item at a specific ledger version from the table identified by table handle.
		///
		/// @param _table_handle   Table handle hex encoded 32-byte string.
		/// @param _ledger_version Ledger version to get state of account.
		/// @param _payload        The table item request containing the key_type, value_type and key.
		/// @param _callback       A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetTableItem(FString _table_handle, FString _ledger_version, FString _payload, const FAptosCallCompleteDynamicDelegate& _callback);

		/// Gets a raw table item at a specific ledger version from the table identified by table handle.
		///
		/// @param _table_handle   Table handle hex encoded 32-byte string.
		/// @param _ledger_version Ledger version to get state of account.
		/// @param _payload        The table item request containing only key.
		/// @param _callback       A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetRawTableItem(FString _table_handle, FString _ledger_version, FString _payload, const FAptosCallCompleteDynamicDelegate& _callback);

		/// Gets the coin value for an account.
		///
		/// @param _content The response received from GetAccountResource (0x1::coin::CoinStore<0x1::aptos_coin::AptosCoin>).
		/// @param Coin The value output of the coin.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetCoinData(const FString _content, FString& Coin);

		/// Queries collection data.
		///
		/// @param _content         The response received from GetAccountResource (0x1::token::Collections).
		/// @param _collection_name The name of the collection.
		/// @param TableHandle      The table handle output.
		/// @param TableItemRequest The table item request output.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetCollectionData(const FString _content, const FString _collection_name, FString& TableHandle, FString& TableItemRequest);

		/// Queries token data from collection.
		///
		/// @param _content         The response received from GetAccountResource (0x1::token::Collections).
		/// @param _creator         The address who created the token.
		/// @param _collection_name The name of the collection.
		/// @param _token_name      The name of the token.
		/// @param TableHandle      The table handle output.
		/// @param TableItemRequest The table item request output.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetTokenData(const FString _content, const FString _creator, const FString _collection_name, const FString _token_name, FString& TableHandle, FString& TableItemRequest);

		/// Queries token balance for a token account.
		///
		/// @param _content          The response received from GetAccountResource (0x1::token::TokenStore).
		/// @param _property_version Property version.
		/// @param _creator          The address who created the token.
		/// @param _collection_name  The name of the collection.
		/// @param _token_name       The name of the token.
		/// @param TableHandle       The table handle output.
		/// @param TableItemRequest  The table item request output.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetToken(const FString _content, const FString _property_version, const FString _creator, const FString _collection_name, const FString _token_name, FString& TableHandle, FString& TableItemRequest);
};