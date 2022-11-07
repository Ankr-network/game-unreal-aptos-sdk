#pragma once

#import <Foundation/Foundation.h>

typedef int(*DumpMethodHandle)(unsigned char, unsigned long);

class ANKRSDK_API LibraryManager
{
    
public:
    static LibraryManager& GetInstance()
    {
        static LibraryManager INSTANCE;
        return INSTANCE;
    }

private:
    LibraryManager() {}

public:
    LibraryManager(LibraryManager const&) = delete;
    void operator = (LibraryManager const&) = delete;

public:

    void* HNDL = NULL;
    DumpMethodHandle dumpMethod = NULL;
    bool isInitialized;

    void Load();
    void Unload();
    void DumpMethod();

    NSString* FStringToNSString(FString _input);
    FString NSStringToFString(NSString* _input);
};