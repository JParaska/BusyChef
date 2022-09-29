// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "AICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "../Components/CharacterStatsComponent.h"
#include "../Gameplay/SpawnerBase.h"

AAICharacter::AAICharacter() {

}

void AAICharacter::ActivatePoolable() {
	SetActorHiddenInGame(false);
	GetCharacterMovement()->Activate();
	StatsComponent->InitStats();
}

void AAICharacter::SetTransform(const FTransform& Destination) {
	SetActorTransform(Destination);
}

void AAICharacter::DeactivatePoolable() {
	GetCharacterMovement()->Deactivate();
	SetActorHiddenInGame(true);
}

void AAICharacter::ReturnToPool() {
	ASpawnerBase* SpawnerOwner = Cast<ASpawnerBase>(GetOwner());
	if (SpawnerOwner != nullptr) {
		SpawnerOwner->ReturnSpawnedActor(this);
	}
	else {
		// If there is no pool to return to, destroy
		Destroy();
	}
}
