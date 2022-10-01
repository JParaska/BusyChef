// Copyright Epic Games, Inc. All Rights Reserved.


#include "BusyChefGameModeBase.h"

void ABusyChefGameModeBase::SetGameContext(const EGameContext NewContext) {
	const EGameContext OldContext = GameContext;
	GameContext = NewContext;

	OnGameContextChanged.Broadcast(OldContext, NewContext);
}

void ABusyChefGameModeBase::StartNewGame() {
	if (GameContext == EGameContext::MainMenu) {
		SetGameContext(EGameContext::Game); // TODO prompt character selection
	}
}

void ABusyChefGameModeBase::GameWon() {
	if (GameContext == EGameContext::Game) {
		SetGameContext(EGameContext::GameWon);
	}
}

void ABusyChefGameModeBase::GameOver() {
	if (GameContext == EGameContext::Game) {
		SetGameContext(EGameContext::GameOver);
	}
}

void ABusyChefGameModeBase::BackToMainMenu() {
	if (GameContext == EGameContext::Game ||
		GameContext == EGameContext::GameWon ||
		GameContext == EGameContext::GameOver) { // TODO add pause menu
		SetGameContext(EGameContext::MainMenu);
	}
}
