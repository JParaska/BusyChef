// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "SpawnerBase.h"
#include "EnemySpawner.generated.h"

/**
 * 
 */
UCLASS()
class BUSYCHEF_API AEnemySpawner : public ASpawnerBase
{
	GENERATED_BODY()

#pragma region Methods
public:

	virtual void ReturnSpawnedActor(AActor* SpawnedActor) override;
#pragma endregion
};
