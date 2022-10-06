// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "UserWidgetBase.h"
#include "PlayerHudWidget.generated.h"

#pragma region Forward declarations
class UImage;
#pragma endregion

UCLASS()
class BUSYCHEF_API UPlayerHudWidget : public UUserWidgetBase
{
	GENERATED_BODY()
	
#pragma region Properties
protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ReticleImage;
#pragma endregion

#pragma region Methods
public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
#pragma endregion
};
