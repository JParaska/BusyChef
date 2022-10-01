// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types.h"
#include "BusyChefGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameContextChanged, const EGameContext, OldContext, const EGameContext, NewContext);

UCLASS()
class BUSYCHEF_API ABusyChefGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Properties
private:

	EGameContext GameContext = EGameContext::MainMenu;

public:

	UPROPERTY(BlueprintAssignable, Category = "Game context", meta = (AllowPrivateAccess = "true"))
	FOnGameContextChanged OnGameContextChanged;
#pragma endregion
	
#pragma region Methods
public:

	EGameContext GetGameContext() const { return GameContext; }

	void SetGameContext(const EGameContext NewContext);

	FOnGameContextChanged GetOnGameContextChanged() { return OnGameContextChanged; }

	void StartNewGame();

	void GameWon();

	void GameOver();

	void BackToMainMenu();
#pragma endregion
};
