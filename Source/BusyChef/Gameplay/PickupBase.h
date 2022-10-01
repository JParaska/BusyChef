// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Components/PoolableActorInterface.h"
#include "PickupBase.generated.h"

#pragma region Forward declarations
class ACharacterBase;

class USphereComponent;
class UStaticMeshComponent;
#pragma endregion

UCLASS()
class BUSYCHEF_API APickupBase : public AActor, public IPoolableActorInterface
{
	GENERATED_BODY()

#pragma region Properties
private:

	FTimerHandle LifeTimeTimerHandle;

protected:

#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> PickupCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PickupMesh;
#pragma endregion

	/*
	* After its lifetime, pickup will be returned to pool / destroyed
	* -1 = infinite
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	float LifeTime = -1.0f;
#pragma endregion
	
#pragma region Methods
public:	
	// Sets default values for this actor's properties
	APickupBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region IPoolableActorInterface
	virtual void ActivatePoolable() override;

	virtual void SetTransform(const FTransform& Destination) override;

	UFUNCTION(BlueprintCallable, Category = "ActorPool")
	virtual void DeactivatePoolable() override;

	UFUNCTION(BlueprintCallable, Category = "ActorPool")
	virtual void ReturnToPool() override;
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	* Fires, when picks up this pickup
	* Base implementation returns pickup to pool
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void PickedUp(ACharacterBase* Character);
	virtual void PickedUp_Implementation(ACharacterBase* Character);

	UFUNCTION()
	void OnPickupBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
#pragma endregion
};
