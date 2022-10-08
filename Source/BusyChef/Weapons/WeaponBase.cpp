// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "WeaponBase.h"

#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "../Components/ActorPoolComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = SceneRoot;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(RootComponent);

	ProjectilePoolComponent = CreateDefaultSubobject<UActorPoolComponent>(TEXT("Projectile pool"));
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Fire_Implementation() {
	if (CurrentAmmo <= 0 && !bHasInfiniteAmmo) {
		return;
	}

	if (ProjectilePoolComponent != nullptr && Muzzle != nullptr) {
		ProjectilePoolComponent->GetPoolableActor(Muzzle->GetComponentTransform());
		
		if (!bHasInfiniteAmmo) {
			CurrentAmmo = FMath::Clamp(CurrentAmmo - 1, 0, MaxAmmo);
		}
	}
}

void AWeaponBase::AddAmmo(const EWeaponType Type, const int Amount) {
	if (bHasInfiniteAmmo || WeaponType != Type) {
		return;
	}
	
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, MaxAmmo);
}

void AWeaponBase::ResetAmmo() {
	CurrentAmmo = 0;
}

bool AWeaponBase::IsSelectable() const {
	return HasInfiniteAmmo() || CurrentAmmo > 0;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	
	if (Owner != nullptr) {
		Tags.Append(Owner->Tags);
	}
	else if (GetParentActor() != nullptr) {
		Tags.Append(GetParentActor()->Tags);
	}
}
