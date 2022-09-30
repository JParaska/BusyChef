// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "../AICharacter.h"
#include "AICharacterRanged.generated.h"

#pragma region Forward declarations
class UWeaponComponent;
#pragma endregion

/**
 * base class for ranged AI characters
 */
UCLASS()
class BUSYCHEF_API AAICharacterRanged : public AAICharacter
{
	GENERATED_BODY()

#pragma region Properties
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent> WeaponComponent;
#pragma endregion
	
#pragma region Methods
public:

	AAICharacterRanged();

	virtual void AttackStart() override;
	virtual void AttackStop() override;
#pragma endregion
};
