// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetBase.generated.h"

#pragma region Forward declarations
class ACharacterBase;
#pragma endregion

UCLASS()
class BUSYCHEF_API UUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

#pragma region Properties
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacterBase> ShownCharacter;
#pragma endregion

#pragma region Methods
public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void ShowCharacter(ACharacterBase* Character);
#pragma endregion
	
};
