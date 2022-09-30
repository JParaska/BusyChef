// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "AIControllerBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"

void AAIControllerBase::StartLogic(const float AttackRangeEnter, const float AttackRangeLeft) {
	if (BehaviorTreeAsset != nullptr) {
		RunBehaviorTree(BehaviorTreeAsset);
		GetBlackboardComponent()->SetValueAsFloat(FName("AttackRangeEnter"), AttackRangeEnter);
		GetBlackboardComponent()->SetValueAsFloat(FName("AttackRangeLeft"), AttackRangeLeft);
	}
}

void AAIControllerBase::StopLogic(const FString& Reason) {
	BrainComponent->StopLogic(Reason);
}