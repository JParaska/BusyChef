// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

#pragma region Forward declarations
class UCharacterStatsComponent;
#pragma endregion

UCLASS()
class BUSYCHEF_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

#pragma region Properties
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterStatsComponent> StatsComponent;

#pragma endregion

#pragma region Methods
public:
	// Sets default values for this character's properties
	ACharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Death();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void AttackStart();
	virtual void AttackStop();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
#pragma endregion
};
