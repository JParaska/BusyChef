// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "CharacterStatsComponent.h"

#include "../Characters/CharacterBase.h"

// Sets default values for this component's properties
UCharacterStatsComponent::UCharacterStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called every frame
void UCharacterStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsAlive() && HealthRegeneration != 0.0f) {
		CurrentHealth = FMath::Min(MaxHealth, CurrentHealth + (HealthRegeneration * DeltaTime));
	}
}

void UCharacterStatsComponent::InitStats() {
	CurrentHealth = MaxHealth;
}

void UCharacterStatsComponent::UpdateHealth(float DeltaHealth) {
	CurrentHealth = FMath::Clamp(CurrentHealth + DeltaHealth, 0.0f, MaxHealth);
	
	if (CurrentHealth <= 0.0f) {
		ACharacterBase* CharacterOwner = Cast<ACharacterBase>(GetOwner());
		if (CharacterOwner != nullptr) {
			CharacterOwner->Death();
		}
	}
}

float UCharacterStatsComponent::GetHealthPercent() {
	return CurrentHealth / MaxHealth;
}

bool UCharacterStatsComponent::IsAlive() {
	return CurrentHealth > 0.0f;
}

