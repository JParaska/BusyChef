// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "WeaponWidget.h"

#include "Components/ProgressBar.h"

#include "../Characters/CharacterBase.h"
#include "../Weapons/WeaponBase.h"

#include "../Components/WeaponComponent.h"
#include "../Components/ActorPoolComponent.h"

void UWeaponWidget::ShowCharacter(ACharacterBase* Character) {
	Super::ShowCharacter(Character);

	if (Character != nullptr) {
		ShownWeapon = Character->GetWeaponComponent()->GetWeapon(WeaponIndex);
	}
}

void UWeaponWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (AmmoBar == nullptr) {
		return;
	}

	if (ShownWeapon == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Trying to get Weapon %i"), WeaponIndex);
		ShownWeapon = ShownCharacter->GetWeaponComponent()->GetWeapon(WeaponIndex);
	}

	if (ShownWeapon->HasInfiniteAmmo()) {
		const float Max = ShownWeapon->GetProjectilePoolComponent()->GetMaxActiveActors();
		const float Active = ShownWeapon->GetProjectilePoolComponent()->ActiveActorsCount();

		AmmoBar->SetPercent((Max - Active) / Max);
	}
	else {
		AmmoBar->SetPercent((ShownWeapon->GetCurrentAmmo() * 1.0f) / ShownWeapon->GetMaxAmmo());
	}
}
