// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolableActorInterface.h"
#include "../Types.h"
#include "ActorPoolComponent.generated.h"

#pragma region Forward declarations
#pragma endregion

UCLASS( ClassGroup=(Custom), editinlinenew, meta=(BlueprintSpawnableComponent) )
class BUSYCHEF_API UActorPoolComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Properties
protected:

	TQueue<IPoolableActorInterface*, EQueueMode::Mpsc> ActorPool;

	TSet<IPoolableActorInterface*> ActiveActors;

	// Must implement PoolableActorInterface
	UPROPERTY(EditAnywhere, Category = "ActorPool", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> PoolableActorClass;

	UPROPERTY(EditAnywhere, Category = "ActorPool", meta = (AllowPrivateAccess = "true"))
	int MaxActiveActors = 20;
#pragma endregion

#pragma region Methods
public:	
	// Sets default values for this component's properties
	UActorPoolComponent(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	IPoolableActorInterface* GetPoolableActor(const FTransform& Destination);

	void ReturnPoolableActor(IPoolableActorInterface* PooledActor);

	void ReturnAll();

	int ActiveActorsCount() const;

	TSubclassOf<AActor> GetPoolableActorClass() const { return PoolableActorClass; }

	int GetMaxActiveActors() const { return MaxActiveActors; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

	UFUNCTION()
	void OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext);
#pragma endregion
};
