// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Components/PoolableActorInterface.h"
#include "ProjectileBase.generated.h"

UCLASS()
class BUSYCHEF_API AProjectileBase : public AActor, public IPoolableActorInterface
{
	GENERATED_BODY()
	
#pragma region Methods
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region IPoolableActorInterface
	virtual void ActivatePoolable() override;

	UFUNCTION(BlueprintCallable, Category = "ActorPool")
	virtual void DeactivatePoolable() override;
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
#pragma endregion
};
