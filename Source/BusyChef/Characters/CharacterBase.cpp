// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "CharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "../Components/CharacterStatsComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComponent = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("Character stats"));
	GetCharacterMovement()->GravityScale = 0.0f;
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::Death() {
	UE_LOG(LogTemp, Error, TEXT("Override this method in child class"));
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void ACharacterBase::AttackStart() {
	UE_LOG(LogTemp, Error, TEXT("Override in child classes"))
}

void ACharacterBase::AttackStop() {
	UE_LOG(LogTemp, Error, TEXT("Override in child classes"))
}

float ACharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	StatsComponent->UpdateHealth(-ActualDamage);
	return ActualDamage;
}
