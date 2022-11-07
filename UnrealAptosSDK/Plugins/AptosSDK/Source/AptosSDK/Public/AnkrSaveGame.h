#pragma once

#include "GameFramework/SaveGame.h"
#include "AnkrSaveGame.generated.h"

UCLASS()
class APTOSSDK_API UAnkrSaveGame : public USaveGame
{
    GENERATED_BODY()

public:

    UPROPERTY(VisibleAnywhere, Category = "AnkrSDK")
    FString UniqueId;

    static void Save(FString _uniqueId);
    static UAnkrSaveGame* Load();
    static void Erase();
};