// Copyright Epic Games, Inc. All Rights Reserved.

#include "AptosSDK.h"
#include <codecvt>
#include <vector>
#include "Windows/LibraryManager.h"

#define LOCTEXT_NAMESPACE "FAptosSDKModule"

void FAptosSDKModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

#if PLATFORM_WINDOWS
	LibraryManager::GetInstance().Load();
#endif
}

void FAptosSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

#if PLATFORM_WINDOWS
	LibraryManager::GetInstance().Unload();
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAptosSDKModule, AptosSDK)