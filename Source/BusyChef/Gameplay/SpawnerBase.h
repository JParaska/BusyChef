// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerBase.generated.h"

#pragma region Forward declarations
class UActorPoolComponent;
class UBoxComponent;
#pragma endregion

/*
* Base spawner class responsible for spawning poolable objects
*/
UCLASS()
class BUSYCHEF_API ASpawnerBase : public AActor
{
	GENERATED_BODY()

#pragma region Properties
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner", meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<AActor>, UActorPoolComponent*> PoolComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner", meta = (AllowPrivateAccess = "true"))
	TArray<UBoxComponent*> SpawnPoints;

#pragma endregion
	
#pragma region Methods
public:	
	// Sets default values for this actor's properties
	ASpawnerBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void Spawn(const TSubclassOf<AActor>& Type, const int Count);

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	virtual void ReturnSpawnedActor(AActor* SpawnedActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void InitializeSpawner();
#pragma endregion
};
