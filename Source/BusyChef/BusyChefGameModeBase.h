// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types.h"
#include "BusyChefGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameContextChanged, const EGameContext, OldContext, const EGameContext, NewContext);

#pragma region Forward declarations
class AWaveManager;
#pragma endregion

UCLASS()
class BUSYCHEF_API ABusyChefGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Properties
private:

	EGameContext GameContext = EGameContext::MainMenu;

	TObjectPtr<AWaveManager> WaveManager;

public:

	UPROPERTY(BlueprintAssignable, Category = "Game context", meta = (AllowPrivateAccess = "true"))
	FOnGameContextChanged OnGameContextChanged;
#pragma endregion
	
#pragma region Methods
public:

	/*
	* Sets new timer manager if there is none registered
	* 
	* @return false if there was already WaveManager registered, true otherwise
	*/
	bool SetWaveManager(AWaveManager* Manager);

	UFUNCTION(BlueprintPure)
	AWaveManager* GetWaveManager() const { return WaveManager; }

	EGameContext GetGameContext() const { return GameContext; }

	FOnGameContextChanged GetOnGameContextChanged() { return OnGameContextChanged; }

	/*
	* Sets game context to Game
	*/
	void StartNewGame();

	/*
	* Sets game context to pause
	*/
	void PauseGame();

	/*
	* Sets game context to game
	*/
	void ResumeGame();

	/*
	* Sets game context to GameOver
	*/
	void GameOver();

	/*
	* Sets game context to MainMenu
	*/
	void BackToMainMenu();

private:

	void SetGameContext(const EGameContext NewContext);
#pragma endregion
};
