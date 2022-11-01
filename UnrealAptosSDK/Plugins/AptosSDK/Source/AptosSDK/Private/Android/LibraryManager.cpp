#include "LibraryManager.h"
#include "AnkrUtility.h"

const char* ClassID = "com/product/project/class";

JNIEnv*   Env;
jclass    SampleClass;
jmethodID SampleMethod;

void LibraryManager::LoadLibrary()
{
	//TSharedPtr<FJavaClassObject> FJavaClassObject_DumpClass  = MakeShareable(new FJavaClassObject("com/company/product/class", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis));
	//FJavaClassMethod FJavaClassMethod_DumpMethod = FJavaClassObject_DumpClass->GetClassMethod("Dump", "()V");
	//FJavaClassObject_DumpClass->CallMethod<void>(FJavaClassMethod_DumpMethod);
	
	Env = AndroidJavaEnv::GetJavaEnv();

	SampleClass = FAndroidApplication::FindJavaClassGlobalRef(ClassID);
	if (SampleClass == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("LibraryManager.cpp - LoadLibrary - SampleClass could not be found."));
		return;
	}

	SampleMethod = FJavaWrapper::FindStaticMethod(Env, SampleClass, "SampleMethod", "()V", false);
	if (SampleMethod == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("LibraryManager.cpp - LoadLibrary - SampleMethod could not be found."));
		return;
	}
}

void LibraryManager::UnloadLibrary()
{
	// Nothing to do here for now.
}

void LibraryManager::DumpMethod(FString appId, FString deviceId, FString publicAddress, FString language)
{
	if (SampleClass != NULL && SampleMethod != NULL)
	{
		Env->CallStaticVoidMethod(SampleClass, SampleMethod);
	}
}

jobject LibraryManager::GetJString(FString string)
{
	JNIEnv* JEnv   = AndroidJavaEnv::GetJavaEnv();
	jstring local  = JEnv->NewStringUTF(TCHAR_TO_UTF8(*string));
	jstring result = (jstring)JEnv->NewGlobalRef(local);
	JEnv->DeleteLocalRef(local);
	return result;
}

TArray<FString> LibraryManager::GetFStringArrayFromJava(TSharedPtr<FJavaClassObject> javaObject, FJavaClassMethod javaMethod, const char* seperator)
{
	JNIEnv* JEnv = FAndroidApplication::GetJavaEnv();

	jstring javaReturn        = static_cast<jstring>(javaObject->CallMethod<jobject>(javaMethod));
	const char* rawConversion = JEnv->GetStringUTFChars(javaReturn, nullptr);

	FString conversion(UTF8_TO_TCHAR(rawConversion));
	JEnv->ReleaseStringUTFChars(javaReturn, rawConversion);
	JEnv->DeleteGlobalRef(javaReturn);

	TArray<FString> NamesArray;
	FString seperatorFString(seperator);
	conversion.ParseIntoArray(NamesArray, *seperatorFString, true);

	return NamesArray;
}
