// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "UserWidgetBase.h"
#include "WeaponWidget.generated.h"

#pragma region Forward declarations
class AWeaponBase;

class UProgressBar;
#pragma endregion

UCLASS()
class BUSYCHEF_API UWeaponWidget : public UUserWidgetBase
{
	GENERATED_BODY()

#pragma region Properties
protected:

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<AWeaponBase> ShownWeapon;

	UPROPERTY(EditAnywhere, Category = "UI")
	int WeaponIndex;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> AmmoBar;
#pragma endregion

#pragma region Methods
public:

	virtual void ShowCharacter(ACharacterBase* Character) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
#pragma endregion
	
};
