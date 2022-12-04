// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AptosClient.h"
#include "AptosDelegates.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALAPTOSSDK_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category = "AptosSDK")
	FApplicationResume onApplicationResume;

	FDelegateHandle hndl_AppWillEnterBackground;
	FDelegateHandle hndl_AppHasEnteredForground;
	FDelegateHandle hndl_ApplicationWillDeactivate;
	bool lostFocus;

	UMyGameInstance();
	~UMyGameInstance();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AptosSDK")
	UAptosClient* aptosClient;

	UFUNCTION(BlueprintCallable, Category = "AptosSDK")
	UAptosClient* GetAptosClient();


	void OnMobileFocusLost();
	void OnMobileFocusGained();
	void OnMobileAppDeactivated();

	UFUNCTION()
	void OnApplicationResumed();
};
