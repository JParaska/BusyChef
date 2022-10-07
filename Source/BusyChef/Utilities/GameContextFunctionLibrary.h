// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "BCGameplayStatics.h"
#include "GameContextFunctionLibrary.generated.h"

/**
 * Static class with collection of function accessing game context
 */
UCLASS()
class BUSYCHEF_API UGameContextFunctionLibrary : public UBCGameplayStatics
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Game context", meta = (WorldContext = "WorldContextObject"))
	static const EGameContext GetGameContext(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game context", meta = (WorldContext = "WorldContextObject"))
	static void StartNewGame(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game context", meta = (WorldContext = "WorldContextObject"))
	static void GameOver(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game context", meta = (WorldContext = "WorldContextObject"))
	static void BackToMainMenu(const UObject* WorldContextObject);
};
