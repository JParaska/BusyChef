// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "PickupSpawner.h"

#include "../BusyChefGameModeBase.h"
#include "../Components/ActorPoolComponent.h"
#include "../Utilities/GameContextFunctionLibrary.h"

void APickupSpawner::BeginPlay() {
	Super::BeginPlay();

	if (UGameContextFunctionLibrary::GetGameContext(this) == EGameContext::Game) {
		GetWorld()->GetTimerManager().SetTimer(PickupSpawnTimerHandle, this, &APickupSpawner::SeletAndSpawnPickup, PickupSpawnTime, true);
	}

	ABusyChefGameModeBase* GameMode = UGameContextFunctionLibrary::GetBusyChefGameModeBase(this);
	if (GameMode != nullptr) {
		GameMode->OnGameContextChanged.AddDynamic(this, &APickupSpawner::OnGameContextChanged);
	}
}

void APickupSpawner::SeletAndSpawnPickup() {
	if (UGameContextFunctionLibrary::GetGameContext(this) == EGameContext::Game) {
		TArray<TSubclassOf<AActor>> PickupTypes;
		PoolComponents.GetKeys(PickupTypes);

		if (PickupTypes.Num() > 0) {
			int RandomPickup = FMath::RandRange(0, PickupTypes.Num() - 1);
			Spawn(PickupTypes[RandomPickup], 1);
		}
		else {
			GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
			// TODO we have no pickups to spawn, destroy
		}
	}
}

void APickupSpawner::OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext) {
	switch (NewContext) {
	case EGameContext::Pause:
	{
		GetWorld()->GetTimerManager().PauseTimer(PickupSpawnTimerHandle);
		break;
	}
	case EGameContext::Game : {
		if (OldContext == EGameContext::Pause) {
			GetWorld()->GetTimerManager().UnPauseTimer(PickupSpawnTimerHandle);
		}
		else {
			GetWorld()->GetTimerManager().SetTimer(PickupSpawnTimerHandle, this, &APickupSpawner::SeletAndSpawnPickup, PickupSpawnTime, true);
		}
		break;
	}
	}
}
