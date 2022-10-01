// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "CharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "../BusyChefGameModeBase.h"

#include "../Components/CharacterStatsComponent.h"
#include "../Components/WeaponComponent.h"

#include "../Utilities/GameContextFunctionLibrary.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComponent = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("Character stats"));
	GetCharacterMovement()->GravityScale = 0.0f;

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon component"));
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::Death() {
	UE_LOG(LogTemp, Error, TEXT("Override this method in child class"));
}

void ACharacterBase::AttackStart() {
	if (WeaponComponent != nullptr) {
		WeaponComponent->PullTrigger();
	}
}

void ACharacterBase::AttackStop() {
	if (WeaponComponent != nullptr) {
		WeaponComponent->ReleaseTrigger();
	}
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	ABusyChefGameModeBase* GameMode = UGameContextFunctionLibrary::GetBusyChefGameModeBase(this);
	if (GameMode != nullptr) {
		GameMode->OnGameContextChanged.AddDynamic(this, &ACharacterBase::OnGameContextChanged);
	}
}

float ACharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	StatsComponent->UpdateHealth(-ActualDamage);
	return ActualDamage;
}

void ACharacterBase::OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext) { }
