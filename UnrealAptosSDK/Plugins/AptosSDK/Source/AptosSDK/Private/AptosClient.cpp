#include "AptosClient.h"
#include "PayloadBuilder.h"
#include "MathHelper.h"
#include "LibraryManager.h"

UAptosClient::UAptosClient(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {  }

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
			callback.ExecuteIfBound(content, "");
		}, Result, false);
}

void UAptosClient::GetAccountResources(FString _address, FString _qledger_version, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/resources");
	UE_LOG(LogTemp, Warning, TEXT("GetAccountResources - url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetAccountResources: %s"), *content);
			
			callback.ExecuteIfBound(content, "");
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

void UAptosClient::GetEventsByCreationNumber(FString _address, FString _creation_number, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/events/").Append(_creation_number);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetEventsByCreationNumber: %s"), *content);
			callback.ExecuteIfBound(content, "");

		}, Result, false);
}

void UAptosClient::GetEventsByEventHandle(FString _address, FString _event_handle, FString _field_name, int _limit, const FAptosCallCompleteDynamicDelegate& Result)
{
	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/accounts/").Append(_address).Append("/events/").Append(_event_handle).Append("/").Append(_field_name);
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "GET", "", [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetEventsByEventHandle: %s"), *content);
			callback.ExecuteIfBound(content, "");

		}, Result, false);
}

void UAptosClient::GetTableItem(FString _table_handle, FString _ledger_version, FString _payload, const FAptosCallCompleteDynamicDelegate& Result)
{
	UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetTableItem: payload: %s"), *_payload);

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/tables/").Append(_table_handle).Append("/item");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "POST", _payload, [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetTableItem: %s"), *content);
			callback.ExecuteIfBound(content, "");

		}, Result, false);
}

void UAptosClient::GetRawTableItem(FString _table_handle, FString _ledger_version, FString _payload, const FAptosCallCompleteDynamicDelegate& Result)
{
	UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetRawTableItem: payload: %s"), *_payload);

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/tables/").Append(_table_handle).Append("/raw_item");
	UE_LOG(LogTemp, Warning, TEXT("url : %s"), *url);
	SendRequest(url, "POST", _payload, [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAptosClient - GetRawTableItem: %s"), *content);
			callback.ExecuteIfBound(content, "");

		}, Result, false);
}

FAptosAccount UAptosClient::GetAliceAccount()
{
	std::vector<uint8_t> sk
	{
		139, 232, 127, 5, 224, 205, 154, 39, 214, 116, 173, 201, 71, 84, 202, 204, 61, 237, 31, 250, 128, 105, 113, 118, 208, 237, 211, 102, 9, 223, 189, 206, 193, 197, 88, 35, 4, 67, 50, 74, 18, 149, 7, 26, 224, 242, 238, 240, 250, 171, 200, 96, 66, 64, 125, 46, 66, 88, 50, 130, 103, 53, 245, 99
	};

	FAptosAccount alice = FAptosAccount();
	alice.ExtractFromPrivateKey(sk);
	return alice;
}

FAptosAccount UAptosClient::GetBobAccount()
{
	std::vector<uint8_t> sk
	{
		108, 229, 219, 204, 239, 251, 7, 108, 251, 22, 35, 129, 121, 229, 102, 50, 185, 107, 86, 192, 194, 45, 209, 232, 72, 112, 163, 36, 39, 69, 115, 39, 138, 212, 3, 225, 51, 170, 204, 43, 249, 82, 175, 54, 9, 121, 214, 27, 32, 224, 21, 193, 194, 192, 97, 1, 147, 11, 118, 60, 16, 14, 137, 6
	};

	FAptosAccount bob = FAptosAccount();
	bob.ExtractFromPrivateKey(sk);
	return bob;
}

FEncodeSubmissionRequest UAptosClient::GetEncodeSubmissionRequest(FString _sender, FString _sequence_number, FString _max_gas_amount, FString _gas_estimate, FString _expireInSecs, FString _type, FString _function, TArray<FString> _type_arguments, TArray<FArgument> _arguments, TArray<FString> _secondary_signers)
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
				UE_LOG(LogTemp, Warning, TEXT("AptosClient - GetEncodeSubmissionRequest - Empty argument, null array will be used instead."));
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
	payload.type = _type;
	payload.function = _function;
	payload.type_arguments = type_arguments;
	payload.arguments = arguments;
	payload.Update();

	FEncodeSubmissionRequest request;
	request.sender = _sender;
	request.sequence_number = FString::FromInt(FCString::Strtoui64(*_sequence_number, NULL, 10));
	request.max_gas_amount = FString::FromInt(FCString::Strtoui64(*_max_gas_amount, NULL, 10));
	request.gas_unit_price = FString::FromInt(FCString::Strtoui64(*_gas_estimate, NULL, 10));
	request.expiration_timestamp_secs = FString::FromInt(MathHelper::GetExpireTimestamp(FCString::Strtoui64(*_expireInSecs, NULL, 10)));
	request.payload = payload;

	if (!_secondary_signers.IsEmpty())
		request.secondary_signers = _secondary_signers;

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

void UAptosClient::AddArgument(TArray<TSharedPtr<FJsonValue>>& _array, const FString _field)
{
	if (_field.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("AptosClient - AddArgument - _field can not be empty."));
		return;
	}

	TArray<FString> splits;
	_field.ParseIntoArray(splits, *FString("::"), true);

	if (splits.Num() != 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("AptosClient - AddArgument - _field is invalid."));
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

void UAptosClient::GetCoinData(const FString _content, FString& Coin)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(_content);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("AptosClient - GetCoinData - Couldn't deserilize - content: %s"), *_content);
		return;
	}

	TSharedPtr<FJsonObject> data = JsonObject->GetObjectField("data");
	TSharedPtr<FJsonObject> coin = data->GetObjectField("coin");
	FString value = coin->GetStringField("value");
	Coin = value;
}

void UAptosClient::GetCollectionData(const FString _content, const FString _collection_name, FString& TableHandle, FString& TableItemRequest)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(_content);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("AptosClient - GetCollectionData - handle couldn't be found - content: %s"), *_content);
		TableHandle		 = FString("");
		TableItemRequest = FString("");
		return;
	}

	TSharedPtr<FJsonObject> data			= JsonObject->GetObjectField("data");
	TSharedPtr<FJsonObject> collection_data = data->GetObjectField("collection_data");
	FString handle							= collection_data->GetStringField("handle");

	TSharedPtr<FJsonObject> builder = UPayloadBuilder::GetBuilder();
	builder->SetStringField("key_type",   FString("0x1::string::String"));
	builder->SetStringField("value_type", FString("0x3::token::CollectionData"));
	builder->SetStringField("key",        _collection_name);

	TableHandle = handle;
	TableItemRequest = UPayloadBuilder::Build(builder);
}

void UAptosClient::GetTokenData(const FString _content, const FString _creator, const FString _collection_name, const FString _token_name, FString& TableHandle, FString& TableItemRequest)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(_content);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("AptosClient - GetTokenData - handle couldn't be found - content: %s"), *_content);
		TableHandle      = FString("");
		TableItemRequest = FString("");
		return;
	}

	FString type = JsonObject->GetStringField("type");
	TSharedPtr<FJsonObject> data = JsonObject->GetObjectField("data");
	TSharedPtr<FJsonObject> token_data = data->GetObjectField("token_data");
	FString handle = token_data->GetStringField("handle");

	TSharedPtr<FJsonObject> builder = UPayloadBuilder::GetBuilder();
	builder->SetStringField("key_type",   FString("0x3::token::TokenDataId"));
	builder->SetStringField("value_type", FString("0x3::token::TokenData"));

	TSharedPtr<FJsonObject> key = UPayloadBuilder::GetBuilder();
	key->SetStringField("creator",    _creator);
	key->SetStringField("collection", _collection_name);
	key->SetStringField("name",       _token_name);

	builder->SetObjectField("key", key);

	TableHandle = handle;
	TableItemRequest = UPayloadBuilder::Build(builder);
}

void UAptosClient::GetToken(const FString _content, const FString _property_version, const FString _creator, const FString _collection_name, const FString _token_name, FString& TableHandle, FString& TableItemRequest)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(_content);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("AptosClient - GetToken - handle couldn't be found - content: %s"), *_content);
		TableHandle = FString("");
		TableItemRequest = FString("");
		return;
	}

	FString type = JsonObject->GetStringField("type");
	TSharedPtr<FJsonObject> data = JsonObject->GetObjectField("data");
	TSharedPtr<FJsonObject> tokens = data->GetObjectField("tokens");
	FString handle = tokens->GetStringField("handle");

	TSharedPtr<FJsonObject> token_data_id_object = UPayloadBuilder::GetBuilder();
	token_data_id_object->SetStringField("creator", _creator);
	token_data_id_object->SetStringField("collection", _collection_name);
	token_data_id_object->SetStringField("name", _token_name);

	TSharedPtr<FJsonObject> key_object = UPayloadBuilder::GetBuilder();
	key_object->SetObjectField("token_data_id",    token_data_id_object);
	key_object->SetStringField("property_version", _property_version);

	TSharedPtr<FJsonObject> builder = UPayloadBuilder::GetBuilder();
	builder->SetStringField("key_type",   FString("0x3::token::TokenId"));
	builder->SetStringField("value_type", FString("0x3::token::Token"));
	builder->SetObjectField("key",        key_object);

	TableHandle      = handle;
	TableItemRequest = UPayloadBuilder::Build(builder);
}