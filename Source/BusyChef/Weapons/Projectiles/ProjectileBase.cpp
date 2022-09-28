// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "ProjectileBase.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "../WeaponBase.h"
#include "../../Components/ActorPoolComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile mesh"));
	RootComponent = ProjectileMesh;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Projectile collision"));
	ProjectileCollision->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement"));
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::ActivatePoolable() {
	// TODO enable collision
	SetActorHiddenInGame(false);
	ProjectileMovement->Activate();
	ProjectileMovement->Velocity = GetActorForwardVector().GetSafeNormal() * ProjectileMovement->InitialSpeed;
}

void AProjectileBase::SetTransform(const FTransform& Destination) {
	SetActorTransform(Destination);
}

void AProjectileBase::DeactivatePoolable() {
	// TODO disable collision
	// TODO stop movement
	ProjectileMovement->Deactivate();
	SetActorHiddenInGame(true);
}

void AProjectileBase::ReturnToPool() {
	AWeaponBase* WeaponOwner = Cast<AWeaponBase>(GetOwner());
	if (WeaponOwner != nullptr && WeaponOwner->GetProjectilePoolComponent() != nullptr) {
		WeaponOwner->GetProjectilePoolComponent()->ReturnPoolableActor(this);
	}
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileCollision != nullptr)
		ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnProjectileBeginOverlap);
}

void AProjectileBase::ProjectileHit_Implementation(AActor* Actor) {
	ReturnToPool();
}

void AProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	ProjectileHit(OtherActor);
}
