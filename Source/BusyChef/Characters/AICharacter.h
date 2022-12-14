// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "../Components/PoolableActorInterface.h"
#include "AICharacter.generated.h"

/**
 * Base class for AI characters
 */
UCLASS()
class BUSYCHEF_API AAICharacter : public ACharacterBase, public IPoolableActorInterface
{
	GENERATED_BODY()

#pragma region Properties
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float AttackRangeEnter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float AttackRangeLeft;
#pragma endregion
	
#pragma region Methods
public:

	AAICharacter();

#pragma region IPoolableActorInterface
	virtual void ActivatePoolable() override;

	virtual void SetTransform(const FTransform& Destination) override;

	UFUNCTION(BlueprintCallable, Category = "ActorPool")
	virtual void DeactivatePoolable() override;

	UFUNCTION(BlueprintCallable, Category = "ActorPool")
	virtual void ReturnToPool() override;
#pragma endregion

	virtual void Death() override;

	virtual void PossessedBy(AController* NewController) override;

protected:

	virtual void OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext) override;
#pragma endregion
};
