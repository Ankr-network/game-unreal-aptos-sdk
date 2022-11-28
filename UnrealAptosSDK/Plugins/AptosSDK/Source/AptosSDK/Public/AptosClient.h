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

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccount(FString _address, FString _ledger_version, const FAptosCallCompleteDynamicDelegate& _result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountResource(FString _address, FString _resource_type, FString _qledger_version, const FAptosCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetLedgerInfo(const FAptosCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetTransactions(int _qlimit, FString _qstart, const FAptosCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void SubmitTransaction(FSubmitTransactionRequest _submitTransactionRequest, const FAptosCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetTransactionByHash(FString _txn_hash, const FAptosCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountTransactions(FString _address, int _plimit, FString _pstart, const FAptosCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void EncodeSubmission(FEncodeSubmissionRequest _encodeSubmissionRequest, const FAptosCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void EstimateGasPrice(const FAptosCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	FAptosAccount GetAliceAccount();
	
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	FAptosAccount GetBobAccount();

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	FEncodeSubmissionRequest GetEncodeSubmissionRequest(FString _sender, FString _sequence_number, FString _max_gas_amount, FString _gas_estimate, FString _expireInSecs, FString _type, FString _function, TArray<FString> _type_arguments, TArray<FString> _arguments, TArray<FString> _secondary_signers);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	FAccountSignature GetTransactionSignature(FAptosAccount _sender, FString _bcsMessage);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	FSubmitTransactionRequest GetTransactionSubmitRequest(FEncodeSubmissionRequest _encodeSubmissionRequest, FAccountSignature _transactionSignature);
};