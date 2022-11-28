#include "AptosUtility.h"

FString UAptosUtility::GetUrl()
{
	return API_DEVELOPMENT_URL;
}

FString UAptosUtility::GetLastRequest()
{
	return LastRequest;
}

void UAptosUtility::SetLastRequest(FString _lastRequest)
{
	LastRequest = _lastRequest;
}