// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "../PickupBase.h"
#include "../../Types.h"
#include "WeaponPickup.generated.h"

#pragma region Forward declarations
class ACharacterBase;
#pragma endregion

UCLASS()
class BUSYCHEF_API AWeaponPickup : public APickupBase
{
	GENERATED_BODY()

#pragma region Properties
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	EWeaponType WeaponType = EWeaponType::StraightLine;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	int AmmoAmount = 10;
#pragma endregion
	
#pragma region Methods
protected:

	virtual void PickedUp_Implementation(ACharacterBase* Character) override;
#pragma endregion	
};
