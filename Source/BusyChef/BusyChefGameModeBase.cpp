// Copyright Epic Games, Inc. All Rights Reserved.

#include "BusyChefGameModeBase.h"

#include "Gameplay/WaveManager.h"

bool ABusyChefGameModeBase::SetWaveManager(AWaveManager* Manager) {
	if (WaveManager != nullptr)
		return false;

	WaveManager = Manager;
	return true;
}

void ABusyChefGameModeBase::StartNewGame() {
	if (GameContext == EGameContext::MainMenu) {
		SetGameContext(EGameContext::Game); // TODO prompt character selection
	}
}

void ABusyChefGameModeBase::GameOver() {
	if (GameContext == EGameContext::Game) {
		SetGameContext(EGameContext::GameOver);
	}
}

void ABusyChefGameModeBase::BackToMainMenu() {
	if (GameContext == EGameContext::Game ||
		GameContext == EGameContext::GameOver) { // TODO add pause menu
		SetGameContext(EGameContext::MainMenu);
	}
}

void ABusyChefGameModeBase::SetGameContext(const EGameContext NewContext) {
	const EGameContext OldContext = GameContext;
	GameContext = NewContext;

	OnGameContextChanged.Broadcast(OldContext, NewContext);
}
