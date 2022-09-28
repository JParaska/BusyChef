// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Components/PoolableActorInterface.h"
#include "ProjectileBase.generated.h"

#pragma region Forward declarations
class UProjectileMovementComponent;
class USphereComponent;
class UStaticMeshComponent;
#pragma endregion

UCLASS()
class BUSYCHEF_API AProjectileBase : public AActor, public IPoolableActorInterface
{
	GENERATED_BODY()

#pragma region Properties
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> ProjectileCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
#pragma endregion
	
#pragma region Methods
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

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
	* Fires, when projectile collision begins overlap other component based on settings.
	* Base implementation returns projectile to pool
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void ProjectileHit(AActor* Actor);
	virtual void ProjectileHit_Implementation(AActor* Actor);

	UFUNCTION()
	void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
#pragma endregion
};
