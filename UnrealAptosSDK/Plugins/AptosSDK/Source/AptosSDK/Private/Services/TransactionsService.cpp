#include "TransactionsService.h"
#include "PayloadBuilder.h"
#include "MathHelper.h"

UTransactionsService::UTransactionsService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {  }

void UTransactionsService::GetTransactions(int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions");
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("TransactionsService - GetTransactions: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}

void UTransactionsService::SubmitTransaction(FSubmitTransactionRequest _submitTransactionRequest, const FAptosCallCompleteDynamicDelegate& _callback)
{
	const FString payload = UPayloadBuilder::Build(_submitTransactionRequest.ToJsonObject());
	UE_LOG(LogTemp, Warning, TEXT("TransactionsService - SubmitTransaction - payload: %s"), *payload);

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions");
	SendRequest(url, "POST", payload, [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("TransactionsService - SubmitTransaction: %s"), *content);

			FPendingTransaction trasaction;
			FJsonObjectConverter::JsonObjectStringToUStruct(content, &trasaction);

			callback.ExecuteIfBound(content, trasaction.hash);
		}, _callback, false);
}

void UTransactionsService::GetTransactionByHash(FString _txn_hash, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions/by_hash/").Append(_txn_hash);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("TransactionsService - GetTransactionByHash: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}

void UTransactionsService::GetTransactionByVersion(FString _txn_version, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions/by_version/").Append(_txn_version);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("TransactionsService - GetTransactionByVersion: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}

void UTransactionsService::GetAccountTransactions(FString _address, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/transactions");
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("TransactionsService - GetAccountTransactions: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}

void UTransactionsService::EncodeSubmission(FEncodeSubmissionRequest _encodeSubmissionRequest, const FAptosCallCompleteDynamicDelegate& _callback)
{
	const FString payload = UPayloadBuilder::Build(_encodeSubmissionRequest.ToJsonObject());
	UE_LOG(LogTemp, Warning, TEXT("TransactionsService - EncodeSubmission: payload: %s"), *payload);

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/transactions/encode_submission");
	SendRequest(url, "POST", payload, [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("TransactionsService - EncodeSubmission: %s"), *content);

			FString bcsEncodedHex = content.TrimQuotes();

			callback.ExecuteIfBound(content, bcsEncodedHex);
		}, _callback, false);
}

void UTransactionsService::EstimateGasPrice(const FAptosCallCompleteDynamicDelegate& _callback)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/estimate_gas_price");
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("TransactionsService - GetAccount: %s"), *content);

			FGasEstimation gasEstimate;
			FJsonObjectConverter::JsonObjectStringToUStruct(content, &gasEstimate, 0, 0);

			callback.ExecuteIfBound(content, FString::FromInt(gasEstimate.gas_estimate));
		}, _callback, false);
}

FEncodeSubmissionRequest UTransactionsService::GetEncodeSubmissionRequest(FString _sender, FString _sequence_number, FString _max_gas_amount, FString _gas_estimate, FString _expireInSecs, FString _type, FString _function, TArray<FString> _type_arguments, TArray<FArgument> _arguments, TArray<FString> _secondary_signers)
{
	TArray<TSharedPtr<FJsonValue>> type_arguments;
	for (int i = 0; i < _type_arguments.Num(); i++)
	{
		UPayloadBuilder::AddArrayItem(type_arguments, _type_arguments[i]);
	}

	TArray<TSharedPtr<FJsonValue>> arguments;
	if (_arguments.Num() > 0)
	{
		for (auto& entry : _arguments)
		{
			if (entry.Item.IsEmpty() && entry.Array.Num() <= 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("TransactionsService - GetEncodeSubmissionRequest - Empty argument, null array will be used instead."));
			}

			if (!entry.Item.IsEmpty())
			{
				AddArgument(arguments, entry.Item);
			}
			else
			{
				TArray<TSharedPtr<FJsonValue>> ArrayField;
				for (auto& field : entry.Array)
				{
					AddArgument(ArrayField, field);
				}
				UPayloadBuilder::AddNestedArray(arguments, ArrayField);
			}
		}
	}

	FTransactionPayload payload;
	payload.type           = _type;
	payload.function       = _function;
	payload.type_arguments = type_arguments;
	payload.arguments      = arguments;
	payload.Update();

	FEncodeSubmissionRequest request;
	request.sender                    = _sender;
	request.sequence_number           = FString::FromInt(FCString::Strtoui64(*_sequence_number, NULL, 10));
	request.max_gas_amount            = FString::FromInt(FCString::Strtoui64(*_max_gas_amount, NULL, 10));
	request.gas_unit_price            = FString::FromInt(FCString::Strtoui64(*_gas_estimate, NULL, 10));
	request.expiration_timestamp_secs = FString::FromInt(MathHelper::GetExpireTimestamp(FCString::Strtoui64(*_expireInSecs, NULL, 10)));
	request.payload                   = payload;

	if (!_secondary_signers.IsEmpty())
		request.secondary_signers = _secondary_signers;

	return request;
}

FTransactionSignature UTransactionsService::SignTransaction(FAptosAccount _sender, FString _bcsMessage)
{
	std::string bcsEncoded             = MathHelper::FStringToStdString(*_bcsMessage);
	std::vector<uint8_t> message_bytes = MathHelper::HexToBytes(bcsEncoded);
	std::vector<uint8_t> signature     = _sender.Sign(message_bytes);

	FTransactionSignature trxSignature;
	trxSignature.type       = FString("ed25519_signature");
	trxSignature.public_key = _sender.PublicKey;
	trxSignature.signature  = MathHelper::StdStringToFString(MathHelper::BytesToHex(signature.data(), signature.size()));
	return trxSignature;
}

FSubmitTransactionRequest UTransactionsService::GetTransactionSubmitRequest(FEncodeSubmissionRequest _encodeSubmissionRequest, FTransactionSignature _transactionSignature)
{
	FSubmitTransactionRequest request;
	request.sender                    = _encodeSubmissionRequest.sender;
	request.sequence_number           = _encodeSubmissionRequest.sequence_number;
	request.max_gas_amount            = _encodeSubmissionRequest.max_gas_amount;
	request.gas_unit_price            = _encodeSubmissionRequest.gas_unit_price;
	request.expiration_timestamp_secs = _encodeSubmissionRequest.expiration_timestamp_secs;
	request.payload                   = _encodeSubmissionRequest.payload;
	request.signature                 = _transactionSignature;
	return request;
}

void UTransactionsService::AddArgument(TArray<TSharedPtr<FJsonValue>>& _array, const FString _field)
{
	if (_field.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("TransactionsService - AddArgument - _field can not be empty."));
		return;
	}

	TArray<FString> splits;
	_field.ParseIntoArray(splits, *FString("::"), true);

	if (splits.Num() != 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("TransactionsService - AddArgument - _field is invalid."));
		return;
	}

	const FString key = splits[0];
	const FString val = splits[1];

	if (key.Equals(TEXT("null"), ESearchCase::CaseSensitive))
	{
		_array.Add(MakeShareable(new FJsonValueNull()));
	}
	else if (key.Equals(TEXT("string"), ESearchCase::CaseSensitive))
	{
		_array.Add(MakeShareable(new FJsonValueString(val)));
	}
	else if (key.Equals(TEXT("bool"), ESearchCase::CaseSensitive))
	{
		bool value = val.ToBool();
		_array.Add(MakeShareable(new FJsonValueBoolean(value)));
	}
	else if (key.Equals(TEXT("int32"), ESearchCase::CaseSensitive))
	{
		int32 value = FCString::Atoi(*val);
		_array.Add(MakeShareable(new FJsonValueNumber(value)));
	}
	else if (key.Equals(TEXT("int64"), ESearchCase::CaseSensitive))
	{
		int64 value = FCString::Atoi64(*val);
		_array.Add(MakeShareable(new FJsonValueNumber(value)));
	}
	else if (key.Equals(TEXT("uint64"), ESearchCase::CaseSensitive))
	{
		uint64 value = FCString::Strtoui64(*val, NULL, 10);
		_array.Add(MakeShareable(new FJsonValueNumber(value)));
	}
	else if (key.Equals(TEXT("float"), ESearchCase::CaseSensitive))
	{
		float value = FCString::Atof(*val);
		_array.Add(MakeShareable(new FJsonValueNumber(value)));
	}
	else if (key.Equals(TEXT("double"), ESearchCase::CaseSensitive))
	{
		double value = FCString::Atod(*val);
		_array.Add(MakeShareable(new FJsonValueNumber(value)));
	}
}