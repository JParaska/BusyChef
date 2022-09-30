// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "AICharacterRanged.h"

#include "../../Components/WeaponComponent.h"

AAICharacterRanged::AAICharacterRanged() {
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon component"));
}

void AAICharacterRanged::AttackStart() {
	if (WeaponComponent != nullptr) {
		WeaponComponent->PullTrigger();
	}
}

void AAICharacterRanged::AttackStop() {
	if (WeaponComponent != nullptr) {
		WeaponComponent->ReleaseTrigger();
	}
}
