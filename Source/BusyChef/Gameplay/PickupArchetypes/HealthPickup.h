// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "../PickupBase.h"
#include "HealthPickup.generated.h"

UCLASS()
class BUSYCHEF_API AHealthPickup : public APickupBase
{
	GENERATED_BODY()

#pragma region Properties
protected:

	UPROPERTY(EditDefaultsOnly, category = "Pickup")
	float HealAmmount = 10.0f;
#pragma endregion

#pragma region Methods
protected:

	virtual void PickedUp_Implementation(ACharacterBase* Character) override;
#pragma endregion	
};
