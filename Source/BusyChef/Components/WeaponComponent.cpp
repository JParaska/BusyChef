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
}

void UWeaponComponent::ReleaseTrigger() {
	GetWorld()->GetTimerManager().ClearTimer(FireWeaponHandle);
}

void UWeaponComponent::FireWeapon() {
	if (Weapons[SelectedWeapon] == nullptr)
		return;

	Weapons[SelectedWeapon]->Fire();
}

void UWeaponComponent::NextWeapon() {
	if (Weapons.Num() == 1)
		return;

	Weapons[SelectedWeapon]->SelectWeapon(false);

	SelectedWeapon = SelectedWeapon + 1 >= Weapons.Num() ? 0 : SelectedWeapon + 1;

	Weapons[SelectedWeapon]->SelectWeapon(true);

	ReleaseTrigger();
}

void UWeaponComponent::PreviousWeapon() {
	if (Weapons.Num() == 1)
		return;

	Weapons[SelectedWeapon]->SelectWeapon(false);

	SelectedWeapon = SelectedWeapon - 1 < 0 ? Weapons.Num() - 1 : SelectedWeapon - 1;

	Weapons[SelectedWeapon]->SelectWeapon(true);

	ReleaseTrigger();
}

void UWeaponComponent::SelectDefaultWeapon() {
	if (Weapons.Num() == 0)
		return;

	Weapons[0]->SelectWeapon(true);

	if (Weapons.Num() > 1) {
		for (int i = 1; i < Weapons.Num(); i++) {
			Weapons[i]->SelectWeapon(false);
		}
	}
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

