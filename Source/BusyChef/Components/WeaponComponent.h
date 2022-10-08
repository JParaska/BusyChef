// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Types.h"
#include "WeaponComponent.generated.h"

#pragma region Forward declarations
class AWeaponBase;
#pragma endregion

/*
* Component for handling assigned weapons to a character
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUSYCHEF_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Properties
private:

	int SelectedWeapon = 0;

	// Timer handle for firing weapon while input is pressed
	FTimerHandle FireWeaponHandle;

protected:

	// Assigned weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<AWeaponBase*> Weapons;
#pragma endregion

#pragma region Methods
public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	* Starts firing selected weapon.
	* This starts timer that periodically fires projectile from selected weapon
	*/
	void PullTrigger();

	/*
	* Stops firing selected weapon
	*/
	void ReleaseTrigger();

	/*
	* Fires selected weapon
	* Actually fires projectile from selected weapon
	*/
	UFUNCTION()
	void FireWeapon();

	/*
	* Selects next available weapon
	*/
	void NextWeapon();

	/*
	* Selects previous available weapon
	*/
	void PreviousWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SelectDefaultWeapon();

	/*
	* Refills ammo to weapon of WeaponType
	*/
	void AddAmmo(const EWeaponType WeaponType, const int Amount);

	AWeaponBase* GetWeapon(const int Index) const;

	UFUNCTION(BlueprintPure, Category = "Weapon")
	AWeaponBase* GetActiveWeapon() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
#pragma endregion
};
