// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "AICharacter.h"

#include "AIControllerBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "../Components/CharacterStatsComponent.h"
#include "../Gameplay/SpawnerBase.h"

AAICharacter::AAICharacter() {
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAICharacter::ActivatePoolable() {
	SetActorHiddenInGame(false);
	GetCharacterMovement()->Activate();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StatsComponent->InitStats();

	AAIControllerBase* AIControllerBase = Cast<AAIControllerBase>(GetController());
	if (AIControllerBase != nullptr) {
		AIControllerBase->StartLogic(AttackRangeEnter, AttackRangeLeft);
	}
}

void AAICharacter::SetTransform(const FTransform& Destination) {
	SetActorTransform(Destination);
}

void AAICharacter::DeactivatePoolable() {
	AAIControllerBase* AIControllerBase = Cast<AAIControllerBase>(GetController());
	if (AIControllerBase != nullptr) {
		AIControllerBase->StopLogic("Ai Character returned to pool");
	}

	AttackStop();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

void AAICharacter::Death() {
	ReturnToPool();
}

void AAICharacter::PossessedBy(AController* NewController) {
	AActor* PreviousOwner = GetOwner();

	Super::PossessedBy(NewController);

	// If AI character was spawned from pool, set that pool as an owner again
	// TODO check if previous owner is really a pool and contains this AI character
	if (PreviousOwner != nullptr) {
		SetOwner(PreviousOwner);
	}
}
