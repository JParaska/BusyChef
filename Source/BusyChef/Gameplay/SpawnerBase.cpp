// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "SpawnerBase.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Components/ActorPoolComponent.h"
#include "../Components/PoolableActorInterface.h"

// Sets default values
ASpawnerBase::ASpawnerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void ASpawnerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerBase::Spawn(const TSubclassOf<AActor>& Type, const int Count) {
	if (PoolComponents.Contains(Type) && SpawnPoints.Num() > 0) {
		UActorPoolComponent* Pool = PoolComponents[Type];
		for (int i = 0; i < Count; i++) {
			UBoxComponent* RandomSpawnPoint = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)];

			FTransform Destination;
			Destination.SetLocation(UKismetMathLibrary::RandomPointInBoundingBox(RandomSpawnPoint->GetComponentLocation(), RandomSpawnPoint->GetUnscaledBoxExtent()));

			Pool->GetPoolableActor(Destination);
		}
	}
}

void ASpawnerBase::ReturnSpawnedActor(AActor* SpawnedActor) {
	if (PoolComponents.Contains(SpawnedActor->StaticClass())) {
		PoolComponents[SpawnedActor->StaticClass()]->ReturnPoolableActor(Cast<IPoolableActorInterface>(SpawnedActor));
	}
}

// Called when the game starts or when spawned
void ASpawnerBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeSpawner();
}

void ASpawnerBase::InitializeSpawner() {
	PoolComponents.Empty();

	TArray<UActorPoolComponent*> ActorPools;
	GetComponents(ActorPools);
	for (UActorPoolComponent* PoolComponent : ActorPools) {
		if (PoolComponent != nullptr) {
			PoolComponents.Add(PoolComponent->GetPoolableActorClass(), PoolComponent);
		}
	}

	GetComponents(SpawnPoints);
}
