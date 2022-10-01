// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "PickupBase.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "SpawnerBase.h"
#include "../Characters/CharacterBase.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup mesh"));
	RootComponent = PickupMesh;

	PickupCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup collision"));
	PickupCollision->SetupAttachment(RootComponent);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupBase::ActivatePoolable() {
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetActorHiddenInGame(false);

	if (LifeTime > 0) {
		GetWorld()->GetTimerManager().SetTimer(LifeTimeTimerHandle, this, &APickupBase::ReturnToPool, LifeTime, false, LifeTime);
	}
}

void APickupBase::SetTransform(const FTransform& Destination) {
	SetActorTransform(Destination);
}

void APickupBase::DeactivatePoolable() {
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetActorHiddenInGame(true);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void APickupBase::ReturnToPool() {
	ASpawnerBase* SpawnerOwner = Cast<ASpawnerBase>(GetOwner());
	if (SpawnerOwner != nullptr) {
		SpawnerOwner->ReturnSpawnedActor(this);
	}
	else {
		// If there is no pool to return to, destroy
		Destroy();
	}
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	if (PickupCollision != nullptr) {
		PickupCollision->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnPickupBeginOverlap);
	}
}

void APickupBase::PickedUp_Implementation(ACharacterBase* Character) {
	ReturnToPool();
}

void APickupBase::OnPickupBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	ACharacterBase* Character = Cast<ACharacterBase>(OtherActor);

	if (Character != nullptr && Character->Tags.Contains("Player")) {
		PickedUp(Character);
	}
}
