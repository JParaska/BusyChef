// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "WeaponComponent.h"

#include "../Weapons/WeaponBase.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::PullTrigger() {
	const float FireRate = Weapons[SelectedWeapon]->GetFireRate();
	GetWorld()->GetTimerManager().SetTimer(FireWeaponHandle, this, &UWeaponComponent::FireWeapon, FireRate, true, 0.1f);
	Weapons[SelectedWeapon]->FireStarted();
}

void UWeaponComponent::ReleaseTrigger() {
	GetWorld()->GetTimerManager().ClearTimer(FireWeaponHandle);
	Weapons[SelectedWeapon]->FireStopped();
}

void UWeaponComponent::FireWeapon() {
	if (Weapons[SelectedWeapon] == nullptr)
		return;

	Weapons[SelectedWeapon]->Fire();

	// When selected weapon runs aout of ammo, select next available
	if (Weapons[SelectedWeapon]->GetCurrentAmmo() <= 0 && !Weapons[SelectedWeapon]->HasInfiniteAmmo()) {
		Weapons[SelectedWeapon]->FireStopped();
		NextWeapon();
	}
}

void UWeaponComponent::NextWeapon() {
	if (Weapons.Num() == 1)
		return;

	// Cycle through weapons, until next selectable weapon is found or we reach selected weapon again
	int WeaponToSelect = SelectedWeapon;
	do {
		WeaponToSelect = WeaponToSelect + 1 >= Weapons.Num() ? 0 : WeaponToSelect + 1;
		if (WeaponToSelect == SelectedWeapon) {
			break;
		}
	} while (!Weapons[WeaponToSelect]->IsSelectable());

	if (WeaponToSelect != SelectedWeapon) {
		Weapons[SelectedWeapon]->SelectWeapon(false);

		SelectedWeapon = WeaponToSelect;

		Weapons[SelectedWeapon]->SelectWeapon(true);

		ReleaseTrigger();
	}
}

void UWeaponComponent::PreviousWeapon() {
	if (Weapons.Num() == 1)
		return;

	// Cycle through weapons, until next selectable weapon is found or we reach selected weapon again
	int WeaponToSelect = SelectedWeapon;
	do {
		WeaponToSelect = WeaponToSelect - 1 < 0 ? Weapons.Num() - 1 : WeaponToSelect - 1;
		if (WeaponToSelect == SelectedWeapon) {
			break;
		}
	} while (!Weapons[WeaponToSelect]->IsSelectable());

	if (WeaponToSelect != SelectedWeapon) {
		Weapons[SelectedWeapon]->SelectWeapon(false);

		SelectedWeapon = WeaponToSelect;

		Weapons[SelectedWeapon]->SelectWeapon(true);

		ReleaseTrigger();
	}
}

void UWeaponComponent::SelectDefaultWeapon() {
	if (Weapons.Num() == 0)
		return;

	SelectedWeapon = 0;
	Weapons[0]->SelectWeapon(true);

	if (Weapons.Num() > 1) {
		for (int i = 1; i < Weapons.Num(); i++) {
			Weapons[i]->SelectWeapon(false);
		}
	}
}

void UWeaponComponent::AddAmmo(const EWeaponType WeaponType, const int Amount) {
	for (AWeaponBase* Weapon : Weapons) {
		if (Weapon->GetWeaponType() == WeaponType) {
			Weapon->AddAmmo(WeaponType, Amount);
			break;
		}
	}
}

AWeaponBase* UWeaponComponent::GetWeapon(const int Index) const {
	return Weapons.IsValidIndex(Index) ? Weapons[Index] : nullptr;
}

AWeaponBase* UWeaponComponent::GetActiveWeapon() const {
	return Weapons[SelectedWeapon];
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

