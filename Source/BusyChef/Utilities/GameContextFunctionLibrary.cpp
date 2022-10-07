// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "GameContextFunctionLibrary.h"

#include "../BusyChefGameModeBase.h"

const EGameContext UGameContextFunctionLibrary::GetGameContext(const UObject* WorldContextObject) {
	ABusyChefGameModeBase* GameMode = GetBusyChefGameModeBase(WorldContextObject);
	return GameMode != nullptr ? GameMode->GetGameContext() : EGameContext::None;
}

void UGameContextFunctionLibrary::StartNewGame(const UObject* WorldContextObject) {
	ABusyChefGameModeBase* GameMode = GetBusyChefGameModeBase(WorldContextObject);
	if (GameMode != nullptr) {
		GameMode->StartNewGame();
	}
}

void UGameContextFunctionLibrary::GameOver(const UObject* WorldContextObject) {
	ABusyChefGameModeBase* GameMode = GetBusyChefGameModeBase(WorldContextObject);
	if (GameMode != nullptr) {
		GameMode->GameOver();
	}
}

void UGameContextFunctionLibrary::BackToMainMenu(const UObject* WorldContextObject) {
	ABusyChefGameModeBase* GameMode = GetBusyChefGameModeBase(WorldContextObject);
	if (GameMode != nullptr) {
		GameMode->BackToMainMenu();
	}
}
