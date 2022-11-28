#include "AptosClient.h"
#include "PayloadBuilder.h"
#include "MathHelper.h"
#include "LibraryManager.h"

UAptosClient::UAptosClient(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UAptosClient::GetAccount(FString _address, FString _qledger_version, const FAptosCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);
			
			FAccountData accountData;
			FJsonObjectConverter::JsonObjectStringToUStruct(content, &accountData, 0, 0);

			callback.ExecuteIfBound(content, accountData.sequence_number);

		}, Result, false);
}

void UAptosClient::GetAccountResource(FString _address, FString _resource_type, FString _qledger_version, const FAptosCallCompleteDynamicDelegate& Result)
{
	FString resource_type = FString(MathHelper::UrlEncode(std::string(MathHelper::FStringToStdString(*_resource_type))).c_str());

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/resource/").Append(resource_type);
	UE_LOG(LogTemp, Warning, TEXT("GetAccountResource - url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccountResource: %s"), *content);
			TSharedPtr<FJsonObject> data = jsonObject->GetObjectField("data");
			TSharedPtr<FJsonObject> coin = data->GetObjectField("coin");
			FString value = coin->GetStringField("value");
			callback.ExecuteIfBound(content, value);
		}, Result, false);
}

void UAptosClient::GetLedgerInfo(const FAptosCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetLedgerInfo: %s"), *content);

			FIndexResponse ledger;
			FJsonObjectConverter::JsonObjectStringToUStruct(content, &ledger);

			callback.ExecuteIfBound(content, FString::FromInt(ledger.chain_id));

		}, Result, false);
}

void UAptosClient::GetTransactions(int _qlimit, FString _qstart, const FAptosCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetTransactions: %s"), *content);
			callback.ExecuteIfBound(content, "");

		}, Result, false);
}

void UAptosClient::SubmitTransaction(FSubmitTransactionRequest _submitTransactionRequest, const FAptosCallCompleteDynamicDelegate& Result)
{
	const FString payload = UPayloadBuilder::Build(_submitTransactionRequest.ToJsonObject());
	UE_LOG(LogTemp, Warning, TEXT("SubmitTransaction: %s"), *payload);


	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions");

	SendRequest(url, "POST", payload, [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - SubmitTransaction: %s"), *content);

			FPendingTransaction trasaction;
			FJsonObjectConverter::JsonObjectStringToUStruct(content, &trasaction);

			callback.ExecuteIfBound(content, trasaction.hash);

		}, Result, false);
}

void UAptosClient::GetTransactionByHash(FString _txn_hash, const FAptosCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions/by_hash/").Append(_txn_hash);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetTransactionByHash: %s"), *content);
			callback.ExecuteIfBound(content, "");

		}, Result, false);
}

void UAptosClient::GetAccountTransactions(FString _address, int _plimit, FString _pstart, const FAptosCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/transactions");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccountTransactions: %s"), *content);
			callback.ExecuteIfBound(content, "");

		}, Result, false);
}

void UAptosClient::EncodeSubmission(FEncodeSubmissionRequest _encodeSubmissionRequest, const FAptosCallCompleteDynamicDelegate& Result)
{
	 const FString payload = UPayloadBuilder::Build(_encodeSubmissionRequest.ToJsonObject());
	 UE_LOG(LogTemp, Warning, TEXT("UAptosClient - EncodeSubmission: payload: %s"), *payload);

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions/encode_submission");
	SendRequest(url, "POST", payload, [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - EncodeSubmission: %s"), *content);
			FString bcsEncodedHex = content.TrimQuotes();

			callback.ExecuteIfBound(content, bcsEncodedHex);

		}, Result, false);
}

void UAptosClient::EstimateGasPrice(const FAptosCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/estimate_gas_price");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccount: %s"), *content);

			FGasEstimation gasEstimate;
			FJsonObjectConverter::JsonObjectStringToUStruct(content, &gasEstimate, 0, 0);

			callback.ExecuteIfBound(content, FString::FromInt(gasEstimate.gas_estimate));

		}, Result, false);
}

FAptosAccount UAptosClient::GetAliceAccount()
{
	std::vector<uint8_t> sk
	{
		255,211,113,35,165,87,101,140,224,222,92,33,154,65,150,110,140,93,2,42,28,171,127,97,43,26,129,71,81,123,43,127,184,15,11,253,79,245,134,84,235,194,101,199,183,86,195,6,154,234,47,136,15,71,94,119,91,201,60,202,25,182,116,124
	};

	FAptosAccount alice = FAptosAccount();
	alice.ExtractFromPrivateKey(sk);
	return alice;
}

FAptosAccount UAptosClient::GetBobAccount()
{
	std::vector<uint8_t> sk
	{
		20,225,26,255,205,22,88,59,107,19,118,175,43,243,114,90,198,51,246,142,39,197,124,171,28,60,58,214,46,21,146,143,18,48,212,127,244,102,145,168,135,173,213,67,205,70,19,246,184,65,43,96,86,181,231,77,73,199,154,39,255,120,32,129
	};

	FAptosAccount bob = FAptosAccount();
	bob.ExtractFromPrivateKey(sk);
	return bob;
}

FEncodeSubmissionRequest UAptosClient::GetEncodeSubmissionRequest(FString _sender, FString _sequence_number, FString _max_gas_amount, FString _gas_estimate, FString _expireInSecs, FString _type, FString _function, TArray<FString> _type_arguments, TArray<FString> _arguments, TArray<FString> _secondary_signers)
{
	FTransactionPayload payload;
	payload.type			  = _type;
	payload.function		  = _function;
	payload.type_arguments	  = _type_arguments;
	payload.arguments	      = _arguments;

	FEncodeSubmissionRequest request;
	request.sender					  = _sender;
	request.sequence_number			  = FString::FromInt(FCString::Strtoui64(*_sequence_number, NULL, 10));
	request.max_gas_amount			  = FString::FromInt(FCString::Strtoui64(*_max_gas_amount, NULL, 10));
	request.gas_unit_price			  = FString::FromInt(FCString::Strtoui64(*_gas_estimate, NULL, 10));
	request.expiration_timestamp_secs = FString::FromInt(MathHelper::GetExpireTimestamp(FCString::Strtoui64(*_expireInSecs, NULL, 10)));
	request.payload					  = payload;

	if(!_secondary_signers.IsEmpty()) 
		request.secondary_signers     = _secondary_signers;
	
	return request;
}

FAccountSignature UAptosClient::GetTransactionSignature(FAptosAccount _sender, FString _bcsMessage)
{
	std::string bcsEncoded			   = MathHelper::FStringToStdString(*_bcsMessage);
	std::vector<uint8_t> message_bytes = MathHelper::HexToBytes(bcsEncoded);
	std::vector<uint8_t> signature     = _sender.Sign(message_bytes);

	FAccountSignature trxSignature;
	trxSignature.type		= FString("ed25519_signature");
	trxSignature.public_key = _sender.PublicKey;
	trxSignature.signature  = MathHelper::StdStringToFString(MathHelper::BytesToHex(signature.data(), signature.size()));
	return trxSignature;
}

FSubmitTransactionRequest UAptosClient::GetTransactionSubmitRequest(FEncodeSubmissionRequest _encodeSubmissionRequest, FAccountSignature _transactionSignature)
{
	FSubmitTransactionRequest request;
	request.sender					  = _encodeSubmissionRequest.sender;
	request.sequence_number			  = _encodeSubmissionRequest.sequence_number;
	request.max_gas_amount			  = _encodeSubmissionRequest.max_gas_amount;
	request.gas_unit_price			  = _encodeSubmissionRequest.gas_unit_price;
	request.expiration_timestamp_secs = _encodeSubmissionRequest.expiration_timestamp_secs;
	request.payload					  = _encodeSubmissionRequest.payload;
	request.signature				  = _transactionSignature;
	return request;
}