// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

#pragma region Forward declarations
class UBehaviorTree;
#pragma endregion

UCLASS()
class BUSYCHEF_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

#pragma region Properties
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
#pragma endregion

#pragma region Methods
public:

	void StartLogic(const float AttackRangeEnter, const float AttackRangeLeft);

	void StopLogic(const FString& Reason);
#pragma endregion
	
};
