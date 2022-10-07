// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "BCGameplayStatics.h"

#include "../BusyChefGameModeBase.h"

ABusyChefGameModeBase* UBCGameplayStatics::GetBusyChefGameModeBase(const UObject* WorldContextObject) {
	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return World != nullptr ? Cast<ABusyChefGameModeBase>(World->GetAuthGameMode()) : nullptr;
}
