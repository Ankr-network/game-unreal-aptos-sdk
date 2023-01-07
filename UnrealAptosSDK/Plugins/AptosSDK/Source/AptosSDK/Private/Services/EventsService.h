#pragma once

#include "AptosClientBase.h"
#include "AptosSchemas.h"
#include "EventsService.generated.h"

/// EventsService class is used to get the transaction events.
UCLASS(Blueprintable, BlueprintType)
class APTOSSDK_API UEventsService : public UAptosClientBase
{
	GENERATED_UCLASS_BODY()

	public:

		/// Returns the transaction events using the creation number.
		///
		/// @param _address         The account's address for which to retrieve the events.
		/// @param _creation_number Creation number corresponding to the event stream originating from the given account.
		/// @param _limit           Max number of events to retrieve.
		/// @param _start           Starting sequence number of events.
		/// @param _callback        A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetEventsByCreationNumber(FString _address, FString _creation_number, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback);

		/// Returns events emitted to the given account matching the specified event type.
		///
		/// @param _address      The account's address for which to retrieve the events.
		/// @param _event_handle Name of struct to lookup event handle.
		/// @param _field_name   Name of field to lookup event handle.
		/// @param _limit        Max number of events to retrieve.
		/// @param _start        Starting sequence number of events.
		/// @param _callback     A callback to be executed when the _callback is successful.
		UFUNCTION(BlueprintCallable, Category = "APTOS SDK")
		void GetEventsByEventHandle(FString _address, FString _event_handle, FString _field_name, int _limit, FString _start, const FAptosCallCompleteDynamicDelegate& _callback);
};