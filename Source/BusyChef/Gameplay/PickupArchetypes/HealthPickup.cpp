// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "HealthPickup.h"

#include "../../Characters/CharacterBase.h"

void AHealthPickup::PickedUp_Implementation(ACharacterBase* Character) {
	if (Character != nullptr) {
		Character->Heal(HealAmmount);
	}

	Super::PickedUp_Implementation(Character);
}
