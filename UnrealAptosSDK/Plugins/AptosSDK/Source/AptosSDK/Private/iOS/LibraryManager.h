#pragma once

#import <Foundation/Foundation.h>

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

    void LoadLibrary();
    void UnloadLibrary();
	void DumpMethod();
    
    NSString* FStringToNSString(FString _input);
    FString NSStringToFString(NSString* _input);
};
