// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Types.h"
#include "WeaponBase.generated.h"

#pragma region Forward declarations
class AProjectileBase;

class UActorPoolComponent;
class UArrowComponent;
class USceneComponent;
class UStaticMeshComponent;
#pragma endregion

UCLASS()
class BUSYCHEF_API AWeaponBase : public AActor
{
	GENERATED_BODY()

#pragma region Properties
protected:

#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> Muzzle;

	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UActorPoolComponent> ProjectilePoolComponent;
#pragma endregion

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType = EWeaponType::StraightLine;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	float FireRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	bool bHasInfiniteAmmo = false;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	int MaxAmmo = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	int CurrentAmmo = 0;
#pragma endregion
	
#pragma region Methods
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Fire();
	virtual void Fire_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void SelectWeapon(bool bSelect);

	UFUNCTION(BlueprintPure, Category = "Weapon")
	UActorPoolComponent* GetProjectilePoolComponent() const { return ProjectilePoolComponent; }

	void AddAmmo(const EWeaponType Type, const int Amount);

	bool IsSelectable() const;

	EWeaponType GetWeaponType() const { return WeaponType; }

	float GetFireRate() const { return FireRate; }

	bool HasInfiniteAmmo() const { return bHasInfiniteAmmo; }

	int GetMaxAmmo() const { return MaxAmmo; }

	int GetCurrentAmmo() const { return CurrentAmmo; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma endregion
};
