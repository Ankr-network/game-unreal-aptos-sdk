#include "LibraryManager.h"
// #include "some header"

void LibraryManager::Load()
{
    // Nothing to do here for now.
}

void LibraryManager::Unload()
{
    // Nothing to do here for now.
}

void LibraryManager::DumpMethod(FString appId, FString deviceId, FString publicAddress, FString language)
{
    //[SomeClass DumpMethod];
}

NSString* LibraryManager::FStringToNSString(FString _input)
{
    std::string source = std::string(TCHAR_TO_UTF8(*_input));
    NSString* conversion = [[NSString alloc] initWithUTF8String:source.c_str()];
    return conversion;
}
FString LibraryManager::NSStringToFString(NSString* _input)
{
    FString conversion([_input UTF8String]);
    return conversion;
}
