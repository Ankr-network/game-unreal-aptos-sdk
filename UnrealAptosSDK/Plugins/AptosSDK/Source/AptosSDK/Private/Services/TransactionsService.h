#pragma once

#include "AptosClientBase.h"
#include "AptosSchemas.h"
#include "TransactionsService.generated.h"

/// TransactionsService class is used to create, encode, sign and submit a transaction to Aptos blockchain.
UCLASS(Blueprintable, BlueprintType)
class APTOSSDK_API UTransactionsService : public UAptosClientBase
{
	GENERATED_UCLASS_BODY()

	public:

		/// Retrieves on-chain committed transactions. The page size and start ledger version can be provided to get a specific sequence of transactions.
		///
		/// @param _limit    Max number of transactions to retrieve.
		/// @param _start    Ledger version to start list of transactions.
		/// @param _callback A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetTransactions(int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback);

		/// Submits a signed transaction encoded as BCS (Binary Canonical Serialization).
		///
		/// @param _submitTransactionRequest A request to submit a transaction containing its signature.
		/// @param _callback                 A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void SubmitTransaction(FSubmitTransactionRequest _submitTransactionRequest, const FAptosCallCompleteDynamicDelegate& _callback);

		/// Looks up a committed transaction on-chain or a pending transaction from memory pool by its hash.
		///
		/// @param _txn_hash The hash of a transaction to retrieve.
		/// @param _callback A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetTransactionByHash(FString _txn_hash, const FAptosCallCompleteDynamicDelegate& _callback);

		/// Retrieves a transaction by a given version.
		///
		/// @param _txn_version The version of a transaction to retrieve.
		/// @param _callback    A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetTransactionByVersion(FString _txn_version, const FAptosCallCompleteDynamicDelegate& _callback);

		/// Retrieves on-chain committed transactions from an account.
		///
		/// @param _address  The address of account with or without 0x prefix                                                  .
		/// @param _limit    Max number of transactions to retrieve.
		/// @param _start    Ledger version to start list of transactions.
		/// @param _callback A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetAccountTransactions(FString _address, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback);

		/// Validates the request format, and then gets a response encoded message in a BCS format.
		///
		/// @param _encodeSubmissionRequest Request to encode a submission in BCS.
		/// @param _callback                A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void EncodeSubmission(FEncodeSubmissionRequest _encodeSubmissionRequest, const FAptosCallCompleteDynamicDelegate& _callback);

		/// Gets the gas estimation by taking the median of the last 100,000 transactions.
		///
		/// @param _callback A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void EstimateGasPrice(const FAptosCallCompleteDynamicDelegate& _callback);

		/// Generates an encode submission request ready to send for encode submission.
		///
		/// @param _sender            Account address of the sender.
		/// @param _sequence_number   Sequence number of this transaction. This must match the sequence number stored in the sender's account at the time the transaction executes.
		/// @param _max_gas_amount    Maximum total gas to spend for this transaction.
		/// @param _gas_estimate      Price to be paid per gas unit.
		/// @param _expireInSecs      The blockchain timestamp at which the blockchain would discard this transaction.
		/// @param _type              entry_function_payload.
		/// @param _function          The function id of an entry function defined on-chain.
		/// @param _type_arguments    Type arguments of the function.
		/// @param _arguments         The arguments of the function.
		/// @param _secondary_signers Any Secondary signers to sign the transaction.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		FEncodeSubmissionRequest GetEncodeSubmissionRequest(FString _sender, FString _sequence_number, FString _max_gas_amount, FString _gas_estimate, FString _expireInSecs, FString _type, FString _function, TArray<FString> _type_arguments, TArray<FArgument> _arguments, TArray<FString> _secondary_signers);

		/// Signs a BCS encoded message with the sender's account.
		///
		/// @param _sender     Account of the sender.
		/// @param _bcsMessage A BCS encoded message.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		FTransactionSignature SignTransaction(FAptosAccount _sender, FString _bcsMessage);

		/// Generates a signed transaction (encoded as BCS) request ready to submit.
		///
		/// @param _encodeSubmissionRequest An encode submission request encoded as BCS.
		/// @param _transactionSignature    The signature of the transaction signed by the sender.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		FSubmitTransactionRequest GetTransactionSubmitRequest(FEncodeSubmissionRequest _encodeSubmissionRequest, FTransactionSignature _transactionSignature);

		/// Adds a custom data type to an Array for json serialization.
		///
		/// @param _array The source array.
		/// @param _field The custom data type to be added to the source array.
		void AddArgument(TArray<TSharedPtr<FJsonValue>>& _array, const FString _field);
};