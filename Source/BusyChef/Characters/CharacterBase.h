// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Types.h"
#include "CharacterBase.generated.h"

#pragma region Forward declarations
class UCharacterStatsComponent;
class UWeaponComponent;
#pragma endregion

UCLASS()
class BUSYCHEF_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

#pragma region Properties
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterStatsComponent> StatsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent> WeaponComponent;

#pragma endregion

#pragma region Methods
public:
	// Sets default values for this character's properties
	ACharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Death();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackStart();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackStop();

	void Heal(const float Amount);

	void AddAmmo(const EWeaponType WeaponType, const float Amount);

	UWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	virtual void OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext);
#pragma endregion
};
