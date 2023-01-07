#include "TablesService.h"
#include "PayloadBuilder.h"
#include "MathHelper.h"

UTablesService::UTablesService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {  }

void UTablesService::GetTableItem(FString _table_handle, FString _ledger_version, FString _payload, const FAptosCallCompleteDynamicDelegate& _callback)
{
	UE_LOG(LogTemp, Warning, TEXT("TablesService - GetTableItem: payload: %s"), *_payload);

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/tables/").Append(_table_handle).Append("/item");
	SendRequest(url, "POST", _payload, [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("TablesService - GetTableItem: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}

void UTablesService::GetRawTableItem(FString _table_handle, FString _ledger_version, FString _payload, const FAptosCallCompleteDynamicDelegate& _callback)
{
	UE_LOG(LogTemp, Warning, TEXT("TablesService - GetRawTableItem: payload: %s"), *_payload);

	FString url = FString("https://fullnode.devnet.aptoslabs.com/v1/tables/").Append(_table_handle).Append("/raw_item");
	SendRequest(url, "POST", _payload, [this](const TArray<uint8> bytes, const FString content, const FAptosCallCompleteDynamicDelegate& callback, TSharedPtr<FJsonObject> jsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("TablesService - GetRawTableItem: %s"), *content);

			callback.ExecuteIfBound(content, "");
		}, _callback, false);
}

void UTablesService::GetCoinData(const FString _content, FString& Coin)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(_content);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("TablesService - GetCoinData - Couldn't deserilize - content: %s"), *_content);
		return;
	}

	TSharedPtr<FJsonObject> data = JsonObject->GetObjectField("data");
	TSharedPtr<FJsonObject> coin = data->GetObjectField("coin");
	FString value                = coin->GetStringField("value");
	Coin                         = value;
}

void UTablesService::GetCollectionData(const FString _content, const FString _collection_name, FString& TableHandle, FString& TableItemRequest)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(_content);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("TablesService - GetCollectionData - handle couldn't be found - content: %s"), *_content);
		TableHandle      = FString("");
		TableItemRequest = FString("");
		return;
	}

	TSharedPtr<FJsonObject> data            = JsonObject->GetObjectField("data");
	TSharedPtr<FJsonObject> collection_data = data->GetObjectField("collection_data");
	FString handle                          = collection_data->GetStringField("handle");

	TSharedPtr<FJsonObject> builder = UPayloadBuilder::GetBuilder();
	builder->SetStringField("key_type",   FString("0x1::string::String"));
	builder->SetStringField("value_type", FString("0x3::token::CollectionData"));
	builder->SetStringField("key",        _collection_name);

	TableHandle      = handle;
	TableItemRequest = UPayloadBuilder::Build(builder);
}

void UTablesService::GetTokenData(const FString _content, const FString _creator, const FString _collection_name, const FString _token_name, FString& TableHandle, FString& TableItemRequest)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(_content);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("TablesService - GetTokenData - handle couldn't be found - content: %s"), *_content);
		TableHandle      = FString("");
		TableItemRequest = FString("");
		return;
	}

	FString type                       = JsonObject->GetStringField("type");
	TSharedPtr<FJsonObject> data       = JsonObject->GetObjectField("data");
	TSharedPtr<FJsonObject> token_data = data->GetObjectField("token_data");
	FString handle                     = token_data->GetStringField("handle");

	TSharedPtr<FJsonObject> builder = UPayloadBuilder::GetBuilder();
	builder->SetStringField("key_type",   FString("0x3::token::TokenDataId"));
	builder->SetStringField("value_type", FString("0x3::token::TokenData"));

	TSharedPtr<FJsonObject> key = UPayloadBuilder::GetBuilder();
	key->SetStringField("creator",    _creator);
	key->SetStringField("collection", _collection_name);
	key->SetStringField("name",       _token_name);

	builder->SetObjectField("key", key);

	TableHandle      = handle;
	TableItemRequest = UPayloadBuilder::Build(builder);
}

void UTablesService::GetToken(const FString _content, const FString _property_version, const FString _creator, const FString _collection_name, const FString _token_name, FString& TableHandle, FString& TableItemRequest)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(_content);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("TablesService - GetToken - handle couldn't be found - content: %s"), *_content);
		TableHandle      = FString("");
		TableItemRequest = FString("");
		return;
	}

	FString type                   = JsonObject->GetStringField("type");
	TSharedPtr<FJsonObject> data   = JsonObject->GetObjectField("data");
	TSharedPtr<FJsonObject> tokens = data->GetObjectField("tokens");
	FString handle                 = tokens->GetStringField("handle");

	TSharedPtr<FJsonObject> token_data_id_object = UPayloadBuilder::GetBuilder();
	token_data_id_object->SetStringField("creator",    _creator);
	token_data_id_object->SetStringField("collection", _collection_name);
	token_data_id_object->SetStringField("name",       _token_name);

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