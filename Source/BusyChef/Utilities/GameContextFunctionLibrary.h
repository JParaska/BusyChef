// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../BusyChefGameModeBase.h" // TODO move enums and struct to separate header and make this FD
#include "GameContextFunctionLibrary.generated.h"

#pragma region Forward declarations
//class ABusyChefGameModeBase;
#pragma endregion

/**
 * Static class with collection of function accessing game context
 */
UCLASS()
class BUSYCHEF_API UGameContextFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Game context", meta = (WorldContext = "WorldContextObject"))
	static ABusyChefGameModeBase* GetBusyChefGameModeBase(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Game context", meta = (WorldContext = "WorldContextObject"))
	static const EGameContext GetGameContext(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game context", meta = (WorldContext = "WorldContextObject"))
	static void StartNewGame(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game context", meta = (WorldContext = "WorldContextObject"))
	static void GameWon(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game context", meta = (WorldContext = "WorldContextObject"))
	static void GameOver(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game context", meta = (WorldContext = "WorldContextObject"))
	static void BackToMainMenu(const UObject* WorldContextObject);
};
