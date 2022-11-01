#pragma once

#include "Runtime/Launch/Public/Android/AndroidJNI.h"
#include "Runtime/ApplicationCore/Public/Android/AndroidApplication.h"
#include "Android/AndroidJava.h"

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

	jobject GetJString(FString string);
	TArray<FString> GetFStringArrayFromJava(TSharedPtr<FJavaClassObject> javaObject, FJavaClassMethod javaMethod, const char* seperator);
};
