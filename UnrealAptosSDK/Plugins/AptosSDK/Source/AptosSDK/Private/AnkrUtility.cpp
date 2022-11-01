#include "AnkrUtility.h"

FString UAnkrUtility::GetUrl()
{
	return API_DEVELOPMENT_URL;
}

FString UAnkrUtility::GetLastRequest()
{
	return LastRequest;
}

void UAnkrUtility::SetLastRequest(FString _lastRequest)
{
	LastRequest = _lastRequest;
}