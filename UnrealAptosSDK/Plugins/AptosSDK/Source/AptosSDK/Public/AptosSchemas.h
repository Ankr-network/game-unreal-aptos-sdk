#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "GenericPlatform/GenericPlatform.h"
#include <JsonObjectConverter.h>
#include <string>
#include "AnkrDelegates.h"
#include "AptosSchemas.generated.h"

USTRUCT(BlueprintType)
struct FMoveStructField
{
	GENERATED_BODY()

	UPROPERTY() FString name; // string
	UPROPERTY() FString type; // string
};

USTRUCT(BlueprintType)
struct FMoveStructGenericTypeParam
{
	GENERATED_BODY()

	UPROPERTY() TArray<FString> constraints; // array[string]
};

USTRUCT(BlueprintType)
struct FMoveFunctionGenericTypeParam
{
	GENERATED_BODY()

	UPROPERTY() TArray<FString> constraints; // array[string]
};

USTRUCT(BlueprintType)
struct FMoveStruct
{
	GENERATED_BODY()

	UPROPERTY() FString name;											 // string
	UPROPERTY() bool is_native;											 // boolean
	UPROPERTY() TArray<FString> abilities;								 // array[string]
	UPROPERTY() TArray<FMoveStructGenericTypeParam> generic_type_params; // array[object]
	UPROPERTY() TArray<FMoveStructField> fields;						 // array[object]
};

USTRUCT(BlueprintType)
struct FMoveFunction
{
	GENERATED_BODY()

	UPROPERTY() FString name;											 // string
	UPROPERTY() FString visibility;										 // string
	UPROPERTY() bool is_entry;											 // boolean
	UPROPERTY() TArray<FMoveStructGenericTypeParam> generic_type_params; // array[object]
	UPROPERTY() TArray<FString> params;									 // array[string]
	UPROPERTY() TArray<FString> _return;								 // array[string]
};


USTRUCT(BlueprintType)
struct FCode
{
	GENERATED_BODY()

	UPROPERTY() FString bytecode;
	UPROPERTY() FMoveFunction abi;
};

USTRUCT(BlueprintType)
struct FWriteModule
{
	GENERATED_BODY()

	UPROPERTY() FString address;		// string<hex>
	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FCode data;
};


USTRUCT(BlueprintType)
struct FTransactionPayload
{
	GENERATED_BODY()

	UPROPERTY() FString type;					// string
	UPROPERTY() FString function;				// string
	UPROPERTY() TArray<FString> type_arguments; // array[string]
	UPROPERTY() TArray<FString> arguments;		// array[string]
};

USTRUCT(BlueprintType)
struct FScriptPayload
{
	GENERATED_BODY()

	UPROPERTY() FCode code; // object
	UPROPERTY() TArray<FString> type_arguments; // array[string]
	UPROPERTY() TArray<FString> arguments;		// array[string]
};

USTRUCT(BlueprintType)
struct FWriteSet
{
	GENERATED_BODY()

	UPROPERTY() FString type;		   // string
	UPROPERTY() FString execute_as;    // string<hex>
	UPROPERTY() FScriptPayload script; // object
};



USTRUCT(BlueprintType)
struct FGenesisPayload
{
	GENERATED_BODY()

	UPROPERTY() FString type;		 // string
	UPROPERTY() FWriteSet write_set; // object
};

USTRUCT(BlueprintType)
struct FScriptWriteSet
{
	GENERATED_BODY()

	UPROPERTY() FString execute_as;	   // string<hex>
	UPROPERTY() FScriptPayload script; // object
};

USTRUCT(BlueprintType)
struct FDirectWriteChange
{
	GENERATED_BODY()

	UPROPERTY() FString type;
	UPROPERTY() FString address;
	UPROPERTY() TArray<FString> state_key_hash;
	UPROPERTY() TArray<FString> module;
};

USTRUCT(BlueprintType)
struct FAccountData
{
	GENERATED_BODY()

	UPROPERTY() FString sequence_number;    // string<uint64>
	UPROPERTY() FString authentication_key; // string<hex>
};

USTRUCT(BlueprintType)
struct FAccountSignature
{
	GENERATED_BODY()

	UPROPERTY() FString type;		// string
	UPROPERTY() FString public_key; // string<hex>
	UPROPERTY() FString signature;  // string <hex>
};

USTRUCT(BlueprintType)
struct FAccountSignature_Ed25519Signature
{
	GENERATED_BODY()

	UPROPERTY() FString type;		// string
	UPROPERTY() FString public_key; // string<hex>
	UPROPERTY() FString signature;  // string<hex>
};

USTRUCT(BlueprintType)
struct FAccountSignature_MultiEd25519Signature
{
	GENERATED_BODY()

	UPROPERTY() FString type;				 // string
	UPROPERTY() TArray<FString> public_keys; // array[string]<hex>
	UPROPERTY() TArray<FString> signatures;  // array[string]<hex>
	UPROPERTY() int threshold;				 // integer
	UPROPERTY() FString bitmap;				 // string<hex>
};

/// Address string<hex>

USTRUCT(BlueprintType)
struct FAptosError
{
	GENERATED_BODY()

	UPROPERTY() FString message;	// string
	UPROPERTY() FString error_code; // string
	UPROPERTY() int vm_error_code;  // integer
};

USTRUCT(BlueprintType)
struct FAptosErrorCode
{
	GENERATED_BODY()

	/// string
	/// These codes provide more granular error information beyond just the HTTP status code of the response.
	/// Allowed values : account_not_found resource_not_found module_not_found struct_field_not_found version_not_found transaction_not_found table_item_not_found block_not_found version_pruned block_pruned invalid_input invalid_transaction_update sequence_number_too_old vm_error health_check_failed mempool_is_full internal_error web_framework_error bcs_not_supported api_disabled
};





USTRUCT(BlueprintType)
struct FDecodedTableData
{
	GENERATED_BODY()

	UPROPERTY() FString key;
	UPROPERTY() FString key_type;   // string
	UPROPERTY() FString value;
	UPROPERTY() FString value_type; // string
};

/// Delete a module
USTRUCT(BlueprintType)
struct FDeleteModule
{
	GENERATED_BODY()

	UPROPERTY() FString address;		// string<hex>
	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FString module;			// string
};

/// Delete a resource
USTRUCT(BlueprintType)
struct FDeleteResource
{
	GENERATED_BODY()

	UPROPERTY() FString address;		// string<hex>
	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FString resource;		// string
};



USTRUCT(BlueprintType)
struct FDeletedTableData
{
	GENERATED_BODY()

	UPROPERTY() FString key;	  // Deleted key
	UPROPERTY() FString key_type; // Delete key_type
};

USTRUCT(BlueprintType)
struct FDeleteTableItem
{
	GENERATED_BODY()

	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FString handle;			// string
	UPROPERTY() FString key;			// string
	UPROPERTY() FDeletedTableData data; // object
};



USTRUCT(BlueprintType)
struct FEd25519Signature
{
	GENERATED_BODY()

	UPROPERTY() FString public_key; // string<hex>
	UPROPERTY() FString signature;  // string<hex>
};

USTRUCT(BlueprintType)
struct FEncodeSubmissionRequest
{
	GENERATED_BODY()

	UPROPERTY() FString sender;					   // string<hex>
	UPROPERTY() FString sequence_number;		   // string<uint64>
	UPROPERTY() FString max_gas_amount;			   // string<uint64>
	UPROPERTY() FString gas_unit_price;			   // string<uint64>
	UPROPERTY() FString expiration_timestamp_secs; // string<uint64>
	UPROPERTY() FTransactionPayload payload;	   // object
	UPROPERTY() TArray<FString> secondary_signers; // array[string]<hex>
};

USTRUCT(BlueprintType)
struct FEntryFunctionId
{
	GENERATED_BODY()

	//string
	//Entry function id is string representation of a entry function defined on - chain.
	//Format: {address}::{module name}::{function name}
	//Both module nameand function name are case-sensitive.
	//Example: 0x1::aptos_coin::transfer
};

USTRUCT(BlueprintType)
struct FEntryFunctionPayload
{
	GENERATED_BODY()

	UPROPERTY() FString function;				// string
	UPROPERTY() TArray<FString> type_arguments; // array[string]
	UPROPERTY() TArray<FString> arguments;		// array
};



USTRUCT(BlueprintType)
struct FEventGuid
{
	GENERATED_BODY()

	UPROPERTY() FString creation_number; // string<uint64>
	UPROPERTY() FString account_address; // string<hex>
};

USTRUCT(BlueprintType)
struct FTransactionEvent
{
	GENERATED_BODY()

	UPROPERTY() FEventGuid guid;		 // object
	UPROPERTY() FString sequence_number; // string<uint64>
	UPROPERTY() FString type;			 // string
	UPROPERTY() FString data;
};

USTRUCT(BlueprintType)
struct FDirectWriteSet
{
	GENERATED_BODY()

	UPROPERTY() TArray<FDirectWriteChange> changes; // array[object]
	UPROPERTY() TArray<FTransactionEvent> events;	// array[object]
};

USTRUCT(BlueprintType)
struct FGasEstimation
{
	GENERATED_BODY()

	UPROPERTY() int deprioritized_gas_estimate; // integer
	UPROPERTY() int gas_estimate;				// integer
	UPROPERTY() int prioritized_gas_estimate;	// integer
};



USTRUCT(BlueprintType)
struct FGenesisPayload_WriteSetPayload
{
	GENERATED_BODY()

	UPROPERTY() FString type;		 // string
	UPROPERTY() FWriteSet write_set; // object
};

USTRUCT(BlueprintType)
struct FGenesisTransaction
{
	GENERATED_BODY()

	UPROPERTY() FString version;				    // string<uint64>
	UPROPERTY() FString hash;						// string
	UPROPERTY() FString state_change_hash;			// string
	UPROPERTY() FString event_root_hash;			// string
	UPROPERTY() FString state_checkpoint_hash;		// string
	UPROPERTY() FString gas_used;					// string<uint64>
	UPROPERTY() bool success;						// boolean
	UPROPERTY() FString vm_status;					// string
	UPROPERTY() FString accumulator_root_hash;		// string
	UPROPERTY() TArray<FDirectWriteChange> changes; // array(oneOf)[objects]
	UPROPERTY() FGenesisPayload payload;		    // object
	UPROPERTY() TArray<FTransactionEvent> events;	// array[object]
};

USTRUCT(BlueprintType)
struct FHashValue
{
	GENERATED_BODY()

	// string
};

USTRUCT(BlueprintType)
struct FHealthCheckSuccess
{
	GENERATED_BODY()
	
	UPROPERTY() FString message; // string
};

USTRUCT(BlueprintType)
struct FHexEncodedBytes
{
	GENERATED_BODY()

	/// All bytes (Vec) data is represented as hex-encoded string prefixed with 0x and fulfilled with two hex digits per byte.
	///Unlike the Address type, HexEncodedBytes will not trim any zeros.
	///Example:
	///0x88fbd33f54e1126269769780feb24480428179f552e2313fbe571b72e62a1ca1
};

USTRUCT(BlueprintType)
struct FIdentifierWrapper
{
	GENERATED_BODY()

	// string
};

USTRUCT(BlueprintType)
struct FIndexResponse
{
	GENERATED_BODY()

	UPROPERTY() int chain_id;				   // integer
	UPROPERTY() FString epoch;				   // string<uint64>
	UPROPERTY() FString ledger_version;		   // string<uint64>
	UPROPERTY() FString oldest_ledger_version; // string<uint64>
	UPROPERTY() FString ledger_timestamp;	   // string<uint64>
	UPROPERTY() FString node_role;			   // string
	UPROPERTY() FString oldest_block_height;   // string<uint64>
	UPROPERTY() FString block_height;		   // string<uint64>
	UPROPERTY() FString git_hash;		       // string
};

USTRUCT(BlueprintType)
struct FMoveAbility
{
	GENERATED_BODY()

	// string
};

USTRUCT(BlueprintType)
struct FMoveFunctionVisibility
{
	GENERATED_BODY()

	///string
	///Move function visibility
	///Allowed values : private public friend
};

/// A Move module
USTRUCT(BlueprintType)
struct FMoveModule
{
	GENERATED_BODY()

	UPROPERTY() FString address;						 // string<hex>
	UPROPERTY() FString name;							 // string
	UPROPERTY() TArray<FString> friends;				 // array[string]
	UPROPERTY() TArray<FMoveFunction> exposed_functions; // array[object]
	UPROPERTY() TArray<FMoveStruct> structs;			 // array[object]
};

USTRUCT(BlueprintType)
struct FMoveModuleByteCode
{
	GENERATED_BODY()

	UPROPERTY() FString bytecode; // string<hex>
	UPROPERTY() FMoveModule abi;  // object
};

USTRUCT(BlueprintType)
struct FMoveModuleId
{
	GENERATED_BODY()

	/// string
	/// Move module id is a string representation of Move module.
	/// Format: {address}::{module name} address should be hex - encoded 32 byte account address that is prefixed with 0x.
	/// Module name is case-sensitive.
	/// Example: 0x1::aptos_coin
};

USTRUCT(BlueprintType)
struct FMoveResource
{
	GENERATED_BODY()

	UPROPERTY() FString type; // string
	UPROPERTY() FString data; // object
};

USTRUCT(BlueprintType)
struct FMoveScriptBytecode
{
	GENERATED_BODY()

	UPROPERTY() FString bytecode; // string<hex>
	UPROPERTY() FMoveModule abi; // object
};

USTRUCT(BlueprintType)
struct FMoveStructTag
{
	GENERATED_BODY()

	/// string
	/// String representation of a MoveStructTag(on - chain Move struct type).This exists so you can specify MoveStructTags as path / query parameters, e.g. for get_events_by_event_handle.
	/// It is a combination of :
	/// move_module_address, module_nameand struct_name, all joined by ::
	/// struct generic type parameters joined by,
	/// Examples :
	/// 0x1::coin::CoinStore < 0x1::aptos_coin::AptosCoin>
	/// 0x1::account::Account
	/// Note :
	/// Empty chars should be ignored when comparing 2 struct tag ids.
	/// When used in an URL path, should be encoded by url - encoding(AKA percent - encoding).
};

/// This is a JSON representation of some data within an account resource.More specifically, it is a map of strings to arbitrary JSON values / objects, where the keys are top level fields within the given resource.
USTRUCT(BlueprintType)
struct FMoveStructValue
{
	GENERATED_BODY()

	/// To clarify, you might query for 0x1::account::Account and see the example data.
	/// Move bool type value is serialized into boolean.
	/// Move u8 type value is serialized into integer.
	/// Move u64 and u128 type value is serialized into string.
	/// Move address type value(32 byte Aptos account address) is serialized into a HexEncodedBytes string.For example :
	/// 0x1
	/// 0x1668f6be25668c1a17cd8caf6b8d2f25
	/// Move vector type value is serialized into array, except vector<u8> which is serialized into a HexEncodedBytes string with 0x prefix.For example :
	/// vector<u64>{ 255, 255 } = > ["255", "255"]
	/// vector<u8>{255, 255} = > 0xffff
	/// Move struct type value is serialized into object that looks like this (except some Move stdlib types, see the following section) :
	/// {
	/// 	field1_name: field1_value,
	/// 	field2_name : field2_value,
	/// 	......
	/// }
	/// For example : { "created": "0xa550c18", "role_id" : "0" }
	/// Special serialization for Move stdlib types :
	/// 0x1::string::String is serialized into string.For example, struct value 0x1::string::String{ bytes: b"Hello World!" } is serialized as "Hello World!" in JSON.
};

USTRUCT(BlueprintType)
struct FMoveType
{
	GENERATED_BODY()

	/// string
	/// String representation of an on - chain Move type tag that is exposed in transaction payload.Values: -bool - u8 - u64 - u128 - address - signer - vector : vector < {non - reference MoveTypeId} > -struct : {address}::{module_name}::{struct_name}:: < {generic types} >
	/// Vector type value examples :
	/// -`vector<u8 > `
	/// - `vector<vector<u64 >> `
	/// - `vector<0x1::coin::CoinStore<0x1::aptos_coin::AptosCoin >> `
	/// Struct type value examples :
	/// -`0x1: : coin::CoinStore<0x1::aptos_coin::AptosCoin>
	/// -`0x1: : account::Account`
	/// Note :
	/// 1. Empty chars should be ignored when comparing 2 struct tag ids.
	/// 2. When used in an URL path, should be encoded by url - encoding(AKA percent - encoding).
};

/// An enum of the possible Move value types
USTRUCT(BlueprintType)
struct FMoveValue
{
	GENERATED_BODY()

	// any
};

USTRUCT(BlueprintType)
struct FMultiAgentSignature
{
	GENERATED_BODY()

	UPROPERTY()	FAccountSignature_Ed25519Signature sender;			  // object
	UPROPERTY() TArray<FString> secondary_signer_addresses;			  // array[string]
	UPROPERTY() FAccountSignature_Ed25519Signature secondary_signers; // object
};

USTRUCT(BlueprintType)
struct FMultiEd25519Signature
{
	GENERATED_BODY()
	
	UPROPERTY() TArray<FString> public_keys; // array[string]<hex>
	UPROPERTY() TArray<FString> signatures;  // array[string]<hex>
	UPROPERTY() int threshold;				 // integer
	UPROPERTY() FString bitmap;				 // string<hex>
};

USTRUCT(BlueprintType)
struct FPendingTransaction
{
	GENERATED_BODY()

	UPROPERTY() FString hash;					   // string
	UPROPERTY() FString sender;					   // string<hex>
	UPROPERTY() FString sequence_number;		   // string<uint64>
	UPROPERTY() FString max_gas_amount;			   // string<uint64>
	UPROPERTY() FString gas_unit_price;			   // string<uint64>
	UPROPERTY() FString expiration_timestamp_secs; // string<uint64>
	UPROPERTY() FTransactionPayload payload;	   // object
	UPROPERTY() FAccountData signature;			   // object
};

USTRUCT(BlueprintType)
struct FRoleType
{
	GENERATED_BODY()

	/// string
	/// Allowed values: validator full_node
};



USTRUCT(BlueprintType)
struct FStateCheckpointTransaction
{
	GENERATED_BODY()

	UPROPERTY() FString version;					// string<uint64>
	UPROPERTY() FString hash;						// string
	UPROPERTY() FString state_change_hash;			// string
	UPROPERTY() FString event_root_hash;			// string
	UPROPERTY() FString state_checkpoint_hash;		// string
	UPROPERTY() FString gas_used;					// string<uint64>
	UPROPERTY() bool success;						// boolean
	UPROPERTY() FString vm_status;					// string
	UPROPERTY() FString accumulator_root_hash;		// string
	UPROPERTY() TArray<FDirectWriteChange> changes; // array(oneOf)[objects]
	UPROPERTY() FString timestamp;					// object
};

USTRUCT(BlueprintType)
struct FSubmitTransactionRequest
{
	GENERATED_BODY()

	UPROPERTY() FString sender;					   // string<hex>
	UPROPERTY() FString sequence_number;		   // string<uint64>
	UPROPERTY() FString max_gas_amount;			   // string<uint64>
	UPROPERTY() FString gas_unit_price;			   // string<uint64>
	UPROPERTY() FString expiration_timestamp_secs; // string<uint64>
	UPROPERTY() FTransactionPayload payload;	   // object
	UPROPERTY() FAccountData signature;			   // object
};

USTRUCT(BlueprintType)
struct FTableItemRequest
{
	GENERATED_BODY()

	UPROPERTY() FString key_type;   // string
	UPROPERTY() FString value_type; // string
	UPROPERTY() FString key;
};

USTRUCT(BlueprintType)
struct FTransaction
{
	GENERATED_BODY()

	UPROPERTY() FString type;					   // string
	UPROPERTY() FString hash;					   // string
	UPROPERTY() FString sender;					   // string<hex>
	UPROPERTY() FString sequence_number;		   // string<uint64>
	UPROPERTY() FString max_gas_amount;			   // string<uint64>
	UPROPERTY() FString gas_unit_price;			   // string<uint64>
	UPROPERTY() FString expiration_timestamp_secs; // string<uint64>
	UPROPERTY() FTransactionPayload payload;	   // object
	UPROPERTY() FAccountData signature;			   // object
};



USTRUCT(BlueprintType)
struct FTransactionPayload_EntryFunctionPayload
{
	GENERATED_BODY()

	UPROPERTY() FString type;					// string
	UPROPERTY() FString function;				// string
	UPROPERTY() TArray<FString> type_arguments; // array[string]
	UPROPERTY() TArray<FString> arguments;		// array[string]
};

USTRUCT(BlueprintType)
struct FTransactionPayload_ModuleBundlePayload
{
	GENERATED_BODY()

	UPROPERTY() FString type; // string
	UPROPERTY() TArray<FMoveModule> modules; // array[object]
};

USTRUCT(BlueprintType)
struct FTransactionPayload_ScriptPayload
{
	GENERATED_BODY()

	UPROPERTY() FString type;					// string
	UPROPERTY() FMoveScriptBytecode code;		// object
	UPROPERTY() TArray<FString> type_arguments; // array[string]
	UPROPERTY() TArray<FString> arguments;		// array[string]
};

USTRUCT(BlueprintType)
struct FTransactionSignature
{
	GENERATED_BODY()

	UPROPERTY() FString type;		// string
	UPROPERTY() FString public_key; // string<hex>
	UPROPERTY() FString signature;  // string <hex>
};

USTRUCT(BlueprintType)
struct FTransactionSignature_Ed25519Signature
{
	GENERATED_BODY()

	UPROPERTY() FString type;		// string
	UPROPERTY() FString public_key; // string<hex>
	UPROPERTY() FString signature;  // string <hex>
};

USTRUCT(BlueprintType)
struct FTransactionSignature_MultiAgentSignature
{
	GENERATED_BODY()

	UPROPERTY()	FString type;												  // string
	UPROPERTY()	FAccountSignature_Ed25519Signature sender;					  // object
	UPROPERTY() TArray<FString> secondary_signer_addresses;					  // array[string]<hex>
	UPROPERTY() TArray<FAccountSignature_Ed25519Signature> secondary_signers; // array[object]
};

USTRUCT(BlueprintType)
struct FTransactionSignature_MultiEd25519Signature
{
	GENERATED_BODY()

	UPROPERTY() FString type;				 // string
	UPROPERTY() TArray<FString> public_keys; // array[string]<hex>
	UPROPERTY() TArray<FString> signatures;  // array[string]<hex>
	UPROPERTY() int threshold;				 // integer
	UPROPERTY() FString bitmap;				 // string<hex>
};

USTRUCT(BlueprintType)
struct FTransaction_BlockMetadataTransaction
{
	GENERATED_BODY()

	UPROPERTY() FString type;							   // string
	UPROPERTY() FString version;						   // string<uint64>
	UPROPERTY() FString hash;							   // string
	UPROPERTY() FString state_change_hash;				   // string
	UPROPERTY() FString event_root_hash;				   // string
	UPROPERTY() FString state_checkpoint_hash;			   // string
	UPROPERTY() FString gas_used;						   // string<uint64>
	UPROPERTY() bool success;							   // boolean
	UPROPERTY() FString vm_status;						   // string
	UPROPERTY() FString accumulator_root_hash;			   // string
	UPROPERTY() TArray<FDirectWriteChange> changes;		   // array(oneOf)[objects]
	UPROPERTY() FString id;								   // string
	UPROPERTY() FString epoch;							   // string<uint64>
	UPROPERTY() FString round;							   // string<uint64>
	UPROPERTY() TArray<FTransactionEvent> events;					   // array[object]
	UPROPERTY() TArray<uint8> previous_block_votes_bitvec; // array[integer]<uint8>
	UPROPERTY() FString proposer;						   // string<hex>
	UPROPERTY() TArray<uint32> failed_proposer_indices;    // array[integer]<uint32>
	UPROPERTY() FString timestamp;						   // string<uint64>
};

USTRUCT(BlueprintType)
struct FTransaction_GenesisTransaction
{
	GENERATED_BODY()

	UPROPERTY() FString type;						// string
	UPROPERTY() FString version;					// string<uint64>
	UPROPERTY() FString hash;						// string
	UPROPERTY() FString state_change_hash;			// string
	UPROPERTY() FString event_root_hash;			// string
	UPROPERTY() FString state_checkpoint_hash;		// string
	UPROPERTY() FString gas_used;					// string<uint64>
	UPROPERTY() bool success;						// boolean
	UPROPERTY() FString vm_status;					// string
	UPROPERTY() FString accumulator_root_hash;		// string
	UPROPERTY() TArray<FDirectWriteChange> changes; // array(oneOf)[objects]
	UPROPERTY() FGenesisPayload payload;			// object
	UPROPERTY() TArray<FTransactionEvent> events;	// array[object]
};

USTRUCT(BlueprintType)
struct FTransaction_PendingTransaction
{
	GENERATED_BODY()

	UPROPERTY() FString type;					   // string
	UPROPERTY() FString hash;					   // string
	UPROPERTY() FString sender;					   // string<hex>
	UPROPERTY() FString sequence_number;		   // string<uint64>
	UPROPERTY() FString max_gas_amount;			   // string<uint64>
	UPROPERTY() FString gas_unit_price;			   // string<uint64>
	UPROPERTY() FString expiration_timestamp_secs; // string<uint64>
	UPROPERTY() FTransactionPayload payload;	   // object
	UPROPERTY() FAccountData signature;			   // object
};

USTRUCT(BlueprintType)
struct FTransaction_StateCheckpointTransaction
{
	GENERATED_BODY()

	UPROPERTY() FString type;						// string
	UPROPERTY() FString version;					// string<uint64>
	UPROPERTY() FString hash;						// string
	UPROPERTY() FString state_change_hash;			// string
	UPROPERTY() FString event_root_hash;			// string
	UPROPERTY() FString state_checkpoint_hash;		// string
	UPROPERTY() FString gas_used;					// string<uint64>
	UPROPERTY() bool success;						// boolean
	UPROPERTY() FString vm_status;					// string
	UPROPERTY() FString accumulator_root_hash;		// string
	UPROPERTY() TArray<FDirectWriteChange> changes; // array(oneOf)[objects]
	UPROPERTY() FString timestamp;					// object
};

USTRUCT(BlueprintType)
struct FTransaction_UserTransaction
{
	GENERATED_BODY()

	UPROPERTY() FString type;						// string
	UPROPERTY() FString version;					// string<uint64>
	UPROPERTY() FString hash;						// string
	UPROPERTY() FString state_change_hash;			// string
	UPROPERTY() FString event_root_hash;			// string
	UPROPERTY() FString state_checkpoint_hash;		// string
	UPROPERTY() FString gas_used;					// string<uint64>
	UPROPERTY() bool success;						// boolean
	UPROPERTY() FString vm_status;					// string
	UPROPERTY() FString accumulator_root_hash;		// string
	UPROPERTY() TArray<FDirectWriteChange> changes; // array(oneOf)[objects]
	UPROPERTY() FString sender;						// string<hex>
	UPROPERTY() FString sequence_number;			// string<uint64>
	UPROPERTY() FString max_gas_amount;				// string<uint64>
	UPROPERTY() FString gas_unit_price;				// string<uint64>
	UPROPERTY() FString expiration_timestamp_secs;  // string<uint64>
	UPROPERTY() FTransactionPayload payload;		// object
	UPROPERTY() TArray<FTransactionEvent> events;	// array[object]
	UPROPERTY() FString timestamp;					// string
};

USTRUCT(BlueprintType)
struct FTransactionsBatchSingleSubmissionFailure
{
	GENERATED_BODY()

	UPROPERTY() FAptosError error;	   // object
	UPROPERTY() int transaction_index; // integer
};

USTRUCT(BlueprintType)
struct FTransactionsBatchSubmissionResult
{
	GENERATED_BODY()

	UPROPERTY() TArray<FTransactionsBatchSingleSubmissionFailure> transaction_failures; // array[object]
};

USTRUCT(BlueprintType)
struct FU128
{
	GENERATED_BODY()

	/// string<uint64>
	/// A string containing a 128 - bit unsigned integer.
	/// We represent u128 values as a string to ensure compatibility with languages such as JavaScript that do not parse u64s in JSON natively.
	/// Example: 340282366920938463463374607431768211454
};

USTRUCT(BlueprintType)
struct FU64
{
	GENERATED_BODY()

	/// string<uint64>
	/// A string containing a 64 - bit unsigned integer.
	/// We represent u64 values as a string to ensure compatibility with languages such as JavaScript that do not parse u64s in JSON natively.
	/// Example: 32425224034
};

USTRUCT(BlueprintType)
struct FUserTransaction
{
	GENERATED_BODY()

	UPROPERTY() FString version;							  // string<uint64>
	UPROPERTY() FString hash;								  // string
	UPROPERTY() FString state_change_hash;					  // string
	UPROPERTY() FString event_root_hash;					  // string
	UPROPERTY() FString state_checkpoint_hash;				  // string
	UPROPERTY() FString gas_used;							  // string<uint64>
	UPROPERTY() bool success;								  // boolean
	UPROPERTY() FString vm_status;							  // string
	UPROPERTY() FString accumulator_root_hash;				  // string
	UPROPERTY() TArray<FDirectWriteChange> changes;			  // array(oneOf)[objects]
	UPROPERTY() FString sender;								  // string<hex>
	UPROPERTY() FString sequence_number;					  // string<uint64>
	UPROPERTY() FString max_gas_amount;						  // string<uint64>
	UPROPERTY() FString gas_unit_price;						  // string<uint64>
	UPROPERTY() FString expiration_timestamp_secs;			  // string<uint64>
	UPROPERTY() FTransactionPayload payload;				  // object
	UPROPERTY() FAccountSignature_Ed25519Signature signature; // object
	UPROPERTY() TArray<FTransactionEvent> events;			  // array[object]
	UPROPERTY() FString timestamp;							  // string
};

USTRUCT(BlueprintType)
struct FVersionedEvent
{
	GENERATED_BODY()

	UPROPERTY() FString version;		 // string<uint64>
	UPROPERTY() FEventGuid guid;		 // object
	UPROPERTY() FString sequence_number; // string<uint64>
	UPROPERTY() FString type;			 // string
	UPROPERTY() FString data;
};



USTRUCT(BlueprintType)
struct FWriteResource
{
	GENERATED_BODY()

	UPROPERTY() FString address;		// string
	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FCode data;				// object
};



USTRUCT(BlueprintType)
struct FWriteSetChange
{
	GENERATED_BODY()

	UPROPERTY() FString type;		    // string
	UPROPERTY() FString address;	    // string<hex>
	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FString module;		    // string
};

USTRUCT(BlueprintType)
struct FWriteSetChange_DeleteModule
{
	GENERATED_BODY()

	UPROPERTY() FString type;			// string
	UPROPERTY() FString address;		// string<hex>
	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FString module;			// string
};

USTRUCT(BlueprintType)
struct FWriteSetChange_DeleteResource
{
	GENERATED_BODY()

	UPROPERTY() FString type;		    // string
	UPROPERTY() FString address;	    // string<hex>
	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FString resource;	    // string
};

USTRUCT(BlueprintType)
struct FWriteSetChange_DeleteTableItem
{
	GENERATED_BODY()

	UPROPERTY() FString type;			// string
	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FString handle;			// string<hex>
	UPROPERTY() FString key;			// string<hex>
	UPROPERTY() FDeletedTableData data; // object
};

USTRUCT(BlueprintType)
struct FWriteSetChange_WriteModule
{
	GENERATED_BODY()

	UPROPERTY() FString type;			// string
	UPROPERTY() FString address;		// string<hex>
	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FMoveModule data;		// object
};

USTRUCT(BlueprintType)
struct FWriteSetChange_WriteResource
{
	GENERATED_BODY()

	UPROPERTY() FString type;			// string
	UPROPERTY() FString address;		// string<hex>
	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FMoveResource data;		// object
};

USTRUCT(BlueprintType)
struct FWriteSetChange_WriteTableItem
{
	GENERATED_BODY()

	UPROPERTY() FString type;			// string
	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FString handle;			// string<hex>
	UPROPERTY() FString key;			// string<hex>
	UPROPERTY() FString value;			// string<hex>
	UPROPERTY() FDecodedTableData data; // object
};

USTRUCT(BlueprintType)
struct FWriteSetPayload
{
	GENERATED_BODY()

	UPROPERTY() FWriteSet write_set; // object
};

USTRUCT(BlueprintType)
struct FWriteSet_DirectWriteSet
{
	GENERATED_BODY()

	UPROPERTY() FString type;						// string
	UPROPERTY() TArray<FDirectWriteChange> changes; // array[object]
	UPROPERTY() TArray<FTransactionEvent> events;	// array[object]
};

USTRUCT(BlueprintType)
struct FWriteSet_ScriptWriteSet
{
	GENERATED_BODY()

	UPROPERTY() FString type;		   // string
	UPROPERTY() FString execute_as;	   // string<hex>
	UPROPERTY() FScriptPayload script; // object
};

USTRUCT(BlueprintType)
struct FWriteTableItem
{
	GENERATED_BODY()

	UPROPERTY() FString state_key_hash; // string
	UPROPERTY() FString handle;			// string<hex>
	UPROPERTY() FString key;			// string<hex>
	UPROPERTY() FString value;			// string<hex>
	UPROPERTY() FDecodedTableData data; // object
};



USTRUCT(BlueprintType)
struct FBlock
{
	GENERATED_BODY()

	UPROPERTY() FString block_height;			   // string<uint64>
	UPROPERTY() FString block_hash;				   // string
	UPROPERTY() FString block_timestamp;		   // string<uint64>
	UPROPERTY() FString first_version;			   // string<uint64>
	UPROPERTY() FString last_version;			   // string<uint64>
	UPROPERTY() TArray<FTransaction> transactions; // array[objects]
};

USTRUCT(BlueprintType)
struct FBlockMetadataTransaction
{
	GENERATED_BODY()

	UPROPERTY() FString version;						   // string<uint64>
	UPROPERTY() FString hash;							   // string
	UPROPERTY() FString state_change_hash;				   // string
	UPROPERTY() FString event_root_hash;				   // string
	UPROPERTY() FString state_checkpoint_hash;			   // string
	UPROPERTY() FString gas_used;						   // string<uint64>
	UPROPERTY() bool success;							   // boolean
	UPROPERTY() FString vm_status;						   // string
	UPROPERTY() FString accumulator_root_hash;			   // string
	UPROPERTY() TArray<FDirectWriteChange> changes;		   // array(oneOf)[objects]
	UPROPERTY() FString id;								   // string
	UPROPERTY() FString epoch;							   // string<uint64>
	UPROPERTY() FString round;							   // string<uint64>
	UPROPERTY() TArray<FTransactionEvent> events;		   // array[object]
	UPROPERTY() TArray<uint8> previous_block_votes_bitvec; // array[integer]<uint8>
	UPROPERTY() FString proposer;						   // string<hex>
	UPROPERTY() TArray<uint32> failed_proposer_indices;    // array[integer]<uint32>
	UPROPERTY() FString timestamp;						   // string<uint64>
};

UCLASS()
class APTOSSDK_API UAptosSchemas : public UUserDefinedStruct
{
	GENERATED_BODY()
};
