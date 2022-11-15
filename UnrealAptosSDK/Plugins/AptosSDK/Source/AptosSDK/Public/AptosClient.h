#pragma once

#include "AnkrClientBase.h"
#include "AptosSchemas.h"
#include "AptosClient.generated.h"

/// AptosClient provides various functions that are used to interact with the Aptos blockchain.
UCLASS(Blueprintable, BlueprintType)
class APTOSSDK_API UAptosClient : public UAnkrClientBase
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccount(FString _address, FString _ledger_version, const FAnkrCallCompleteDynamicDelegate& _result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountResources(FString _address, FString _qledger_version, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountModules(FString _address, FString _qledger_version, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountResource(FString _address, FString _resource_type, FString _qledger_version, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountModule(FString _address, FString _module_name, FString _qledger_version, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetBlocksByHeight(FString _block_height, bool qwith_transactions, FString _ledger_version, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetBlocksByVersion(FString _version, bool qwith_transactions, FString _ledger_version, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetEventsByCreationNumber(FString _address, FString _creation_number, int _qlimit, FString _qstart, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetEventsByEventHandle(FString _address, FString _event_handle, FString _field_name, int _qlimit, FString _qstart, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void ShowOpenAPIExplorer(const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void CheckBasicNodeHealth(int _qduration_secs, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetLedgerInfo(const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetTableItem(FString _table_handle, FString _qledger_version, FString _bkey_type, FString _bvalue_type, FString _bkey, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetTransactions(int _qlimit, FString _qstart, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void SubmitTransactions(FString _bsender, FString _bsequence_number, FString _bmax_gas_amount, FString _bgas_unit_price, FString _bexpiration_timestamp_secs, FString _qstart, FSubmitTransactionRequest _submitTransactionRequest, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetTransactionByHash(FString _txn_hash, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetTransactionByVersion(FString _txn_version, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void GetAccountTransactions(FString _address, int _plimit, FString _pstart, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void SubmitBatchTransactions(FString _bsender, FString _bsequence_number, FString _bmax_gas_amount, FString _bgas_unit_price, FString _bexpiration_timestamp_secs, const FAnkrCallCompleteDynamicDelegate& Result);
	
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void SimulateTransactions(FString _bsender, FString _bsequence_number, FString _bmax_gas_amount, FString _bgas_unit_price, FString _bexpiration_timestamp_secs, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void EncodeSubmission(FString _bsender, FString _bsequence_number, FString _bmax_gas_amount, FString _bgas_unit_price, FString _bexpiration_timestamp_secs, FString _type, FString _function, TArray<FString> _type_arguments, TArray<FString> _arguments, const FAnkrCallCompleteDynamicDelegate& Result);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void EstimateGasPrice(const FAnkrCallCompleteDynamicDelegate& Result); 

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void CryptoSignKeyPair(FString& _secretKey, FString& _publicKey);
	
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void CryptoSign(const FString _message, const FString _secretKey, FString& _outSignedMessage);
	
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void CryptoSignDetach(const FString _message, const FString _secretKey, FString& _outSignature);
	
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void CryptoSignEd25519SecretKeyToPublicKey(FString& _publicKey, FString _secretKey);
	
	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void CryptoHashSha256(FString _message,FString& _hash);

	UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
	void RawTransactionTest();
};