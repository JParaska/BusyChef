// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"

/*
* Component for handling stats of a character. E.g. health
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUSYCHEF_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Properties
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats | Survivability", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats | Survivability", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.0f;

	// Per second
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats | Survivability", meta = (AllowPrivateAccess = "true"))
	float HealthRegeneration = 1.0f;
#pragma endregion

#pragma region Methods
public:	
	// Sets default values for this component's properties
	UCharacterStatsComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void InitStats();

	UFUNCTION(BlueprintCallable, Category = "Stats | Survivability")
	void UpdateHealth(float DeltaHealth);

	UFUNCTION(BlueprintPure, Category = "Stats | Survivability")
	float GetHealthPercent();

	UFUNCTION(BlueprintPure, Category = "Stats | Survivability")
	bool IsAlive();
#pragma endregion
		
};
