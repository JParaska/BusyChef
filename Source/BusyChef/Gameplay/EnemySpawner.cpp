// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "EnemySpawner.h"

#include "WaveManager.h"
#include "../Components/ActorPoolComponent.h"
#include "../Utilities/GameContextFunctionLibrary.h"

void AEnemySpawner::ReturnSpawnedActor(AActor* SpawnedActor) {
	Super::ReturnSpawnedActor(SpawnedActor);

	// If there are any active enemies, return
	TArray<UActorPoolComponent*> ActorPools;
	PoolComponents.GenerateValueArray(ActorPools);
	for (const UActorPoolComponent* Pool : ActorPools) {
		if (Pool->ActiveActorsCount() > 0) {
			return;
		}
	}

	// Otherwise, complete wave 
	AWaveManager* WaveManager = Cast<AWaveManager>(GetOwner());
	if (WaveManager != nullptr) {
		WaveManager->FinishWave(UGameContextFunctionLibrary::GetGameContext(this) == EGameContext::Game);
	}
}