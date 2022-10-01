// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "SpawnerBase.h"
#include "../Types.h"
#include "PickupSpawner.generated.h"

#pragma region Forward declarations
class UActorPoolcomponent;
#pragma endregion

UCLASS()
class BUSYCHEF_API APickupSpawner : public ASpawnerBase
{
	GENERATED_BODY()
	
#pragma region Properties
private:

	FTimerHandle PickupSpawnTimerHandle;

protected:

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float PickupSpawnTime;
#pragma endregion

#pragma region Methods
protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void SeletAndSpawnPickup();

	UFUNCTION()
	void OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext);
#pragma endregion
};
