#pragma once

#include "AptosClientBase.h"
#include "AptosSchemas.h"
#include "AptosClient.generated.h"

/// AptosClient provides various functions that are used to interact with the Aptos blockchain.
UCLASS(Blueprintable, BlueprintType)
class APTOSSDK_API UAptosClient : public UAptosClientBase
{
	GENERATED_UCLASS_BODY()

public:

	/// Gets the authentication key and the sequence number for an account address. 
	///
	/// @param _address The address for which the auth key and the sequence number to be received.
	/// @param _qledger_version A version for the ledger or the latest ledger version is retrieved if no version is specified.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccount(FString _address, FString _qledger_version, const FAptosCallCompleteDynamicDelegate& Result);

	/// Gets an individual resource from a given account and at a specific ledger version.
	///
	/// @param _address The address for which the auth key and the sequence number to be received.
	/// @param _resource_type Name of the struct to retrieve.
	/// @param _ledger_version A version for the ledger or the latest ledger version is retrieved if no version is specified.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountResource(FString _address, FString _resource_type, FString _qledger_version, const FAptosCallCompleteDynamicDelegate& Result);

	/// Retrieves all account resources for a given account and a specific ledger version.
	///
	/// @param _address The address for which the auth key and the sequence number to be received.
	/// @param _ledger_version A version for the ledger or the latest ledger version is retrieved if no version is specified.
	/// @param _limit Max number of account resources to retrieve.
	/// @param _start Cursor specifying where to start for pagination.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountResources(FString _address, FString _qledger_version, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& Result);

	/// Gets the latest ledger information, including data such as chain ID, role type, ledger versions, epoch, etc.
	///
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetLedgerInfo(const FAptosCallCompleteDynamicDelegate& Result);
	
	/// Retrieves on-chain committed transactions. The page size and start ledger version can be provided to get a specific sequence of transactions.
	///
	/// @param _qlimit Max number of transactions to retrieve.
	/// @param _qstart Ledger version to start list of transactions.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetTransactions(int _qlimit, FString _qstart, const FAptosCallCompleteDynamicDelegate& Result);

	/// Submits a signed transaction encoded as BCS (Binary Canonical Serialization).
	///
	/// @param _submitTransactionRequest A request to submit a transaction containing its signature.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void SubmitTransaction(FSubmitTransactionRequest _submitTransactionRequest, const FAptosCallCompleteDynamicDelegate& Result);

	/// Looks up a committed transaction on-chain or a pending transaction from memory pool by its hash.
	///
	/// @param _txn_hash The hash of a transaction.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetTransactionByHash(FString _txn_hash, const FAptosCallCompleteDynamicDelegate& Result);

	/// Retrieves on-chain committed transactions from an account.
	///
	/// @param _address The address for which the auth key and the sequence number to be received.
	/// @param _qlimit Max number of transactions to retrieve.
	/// @param _qstart Ledger version to start list of transactions.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountTransactions(FString _address, int _plimit, FString _pstart, const FAptosCallCompleteDynamicDelegate& Result);

	/// Validates the request format, and then returns that request encoded in a BCS message.
	///
	/// @param _encodeSubmissionRequest Request to encode a submission in BCS.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void EncodeSubmission(FEncodeSubmissionRequest _encodeSubmissionRequest, const FAptosCallCompleteDynamicDelegate& Result);

	/// Gets the gas estimation by taking the median of the last 100,000 transactions.
	///
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void EstimateGasPrice(const FAptosCallCompleteDynamicDelegate& Result);

	/// Returns a transaction events using the creation number.
	///
	/// @param _address The account's address for which to retrieve the events.
	/// @param _creation_number Creation number corresponding to the event stream originating from the given account.
	/// @param _limit Max number of events to retrieve.
	/// @param _start Starting sequence number of events.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetEventsByCreationNumber(FString _address, FString _creation_number, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& Result);

	/// Returns events emitted to the given account matching the specified event type.
	///
	/// @param _address The account's address for which to retrieve the events.
	/// @param _event_handle Name of struct to lookup event handle.
	/// @param _field_name Name of field to lookup event handle.
	/// @param _limit Max number of events to retrieve.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetEventsByEventHandle(FString _address, FString _event_handle, FString _field_name, int _limit, const FAptosCallCompleteDynamicDelegate& Result);

	/// Gets a table item at a specific ledger version from the table identified by table handle.
	///
	/// @param _table_handle Table handle hex encoded 32-byte string.
	/// @param _ledger_version Ledger version to get state of account.
	/// @param _payload The table item request containing the key_type, value_type and key.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetTableItem(FString _table_handle, FString _ledger_version, FString _payload, const FAptosCallCompleteDynamicDelegate& Result);

	/// Gets a table item at a specific ledger version from the table identified by table handle.
	///
	/// @param _table_handle Table handle hex encoded 32-byte string.
	/// @param _ledger_version Ledger version to get state of account.
	/// @param _payload The table item request containing only key.
	/// @param Result A callback to be executed when the result is successful.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetRawTableItem(FString _table_handle, FString _ledger_version, FString _payload, const FAptosCallCompleteDynamicDelegate& Result);

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

	/// Generates an encode submission request ready to send for encode submission.
	///
	/// @param _sender Account address of the sender.
	/// @param _sequence_number Sequence number of this transaction. This must match the sequence number stored in the sender's account at the time the transaction executes.
	/// @param _max_gas_amount Maximum total gas to spend for this transaction.
	/// @param _gas_estimate Price to be paid per gas unit.
	/// @param _expireInSecs The blockchain timestamp at which the blockchain would discard this transaction.
	/// @param _type entry_function_payload.
	/// @param _function The function id of an entry function defined on-chain.
	/// @param _type_arguments Type arguments of the function.
	/// @param _arguments The arguments of the function.
	/// @param _secondary_signers Any Secondary signers to sign the transaction.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	FEncodeSubmissionRequest GetEncodeSubmissionRequest(FString _sender, FString _sequence_number, FString _max_gas_amount, FString _gas_estimate, FString _expireInSecs, FString _type, FString _function, TArray<FString> _type_arguments, TArray<FArgument> _arguments, TArray<FString> _secondary_signers);

	/// Signs a BCS encoded message with the sender's account.
	///
	/// @param _sender Account of the sender.
	/// @param _bcsMessage A BCS encoded message.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	FAccountSignature GetTransactionSignature(FAptosAccount _sender, FString _bcsMessage);

	/// Generates a signed transaction (encoded as BCS) request ready to submit.
	///
	/// @param _encodeSubmissionRequest An encode submission request encoded as BCS.
	/// @param _transactionSignature The signature of the transaction signed by the sender.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	FSubmitTransactionRequest GetTransactionSubmitRequest(FEncodeSubmissionRequest _encodeSubmissionRequest, FAccountSignature _transactionSignature);

	/// Adds a custom data type to an Array for json serialization.
	///
	/// @param _array The source array.
	/// @param _field The custom data type to be added to the source array.
	void AddArgument(TArray<TSharedPtr<FJsonValue>>& _array, const FString _field);

	/// Gets the coin value for an account.
	///
	/// @param _content The response received from GetAccountResource (0x1::coin::CoinStore<0x1::aptos_coin::AptosCoin>).
	/// @param Coin The value of the coin.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetCoinData(const FString _content, FString& Coin);

	/// Queries collection data.
	///
	/// @param _content The response received from GetAccountResource (0x1::token::Collections).
	/// @param _collection_name The name of the collection.
	/// @param TableHandle The table handle.
	/// @param TableItemRequest The table item request.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetCollectionData(const FString _content, const FString _collection_name, FString& TableHandle, FString& TableItemRequest);
	
	/// Queries token data from collection.
	///
	/// @param _content The response received from GetAccountResource (0x1::token::Collections).
	/// @param _creator The address who created the token.
	/// @param _collection_name The name of the collection.
	/// @param _token_name The name of the token.
	/// @param TableHandle The table handle.
	/// @param TableItemRequest The table item request.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetTokenData(const FString _content, const FString _creator, const FString _collection_name, const FString _token_name, FString& TableHandle, FString& TableItemRequest);
	
	/// Queries token balance for a token account.
	///
	/// @param _content The response received from GetAccountResource (0x1::token::TokenStore).
	/// @param _property_version Property version.
	/// @param _creator The address who created the token.
	/// @param _collection_name The name of the collection.
	/// @param _token_name The name of the token.
	/// @param TableHandle The table handle.
	/// @param TableItemRequest The table item request.
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetToken(const FString _content, const FString _property_version, const FString _creator, const FString _collection_name, const FString _token_name, FString& TableHandle, FString& TableItemRequest);
};