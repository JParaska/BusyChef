// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "ProjectileBase.h"

#include "../WeaponBase.h"
#include "../../Components/ActorPoolComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::ActivatePoolable() {
	// TODO enable collision
	SetActorHiddenInGame(false);
}

void AProjectileBase::DeactivatePoolable() {
	// TODO disable collision
	SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

}
