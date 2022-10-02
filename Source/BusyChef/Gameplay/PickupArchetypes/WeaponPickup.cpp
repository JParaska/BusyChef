// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "WeaponPickup.h"

#include "../../Characters/CharacterBase.h"

void AWeaponPickup::PickedUp_Implementation(ACharacterBase* Character) {
	if (Character != nullptr) {
		Character->AddAmmo(WeaponType, AmmoAmount);
	}

	Super::PickedUp_Implementation(Character);
}
