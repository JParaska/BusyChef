// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Types.h"
#include "WeaponComponent.generated.h"

#pragma region Forward declarations
class AWeaponBase;
#pragma endregion

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUSYCHEF_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Properties
private:

	int SelectedWeapon = 0;

	FTimerHandle FireWeaponHandle;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<AWeaponBase*> Weapons;
#pragma endregion

#pragma region Methods
public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PullTrigger();

	void ReleaseTrigger();

	UFUNCTION()
	void FireWeapon();

	void NextWeapon();

	void PreviousWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SelectDefaultWeapon();

	void AddAmmo(const EWeaponType WeaponType, const int Amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
#pragma endregion
};
