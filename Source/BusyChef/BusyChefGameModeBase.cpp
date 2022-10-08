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

void ABusyChefGameModeBase::PauseGame() {
	if (GameContext == EGameContext::Game) {
		SetGameContext(EGameContext::Pause);
	}
}

void ABusyChefGameModeBase::ResumeGame() {
	if (GameContext == EGameContext::Pause) {
		SetGameContext(EGameContext::Game);
	}
}

void ABusyChefGameModeBase::GameOver() {
	if (GameContext == EGameContext::Game) {
		SetGameContext(EGameContext::GameOver);
	}
}

void ABusyChefGameModeBase::BackToMainMenu() {
	if (GameContext == EGameContext::Game ||
		GameContext == EGameContext::Pause ||
		GameContext == EGameContext::GameOver) {
		SetGameContext(EGameContext::MainMenu);
	}
}

void ABusyChefGameModeBase::SetGameContext(const EGameContext NewContext) {
	const EGameContext OldContext = GameContext;
	GameContext = NewContext;

	OnGameContextChanged.Broadcast(OldContext, NewContext);
}
