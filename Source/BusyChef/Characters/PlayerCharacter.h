// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"

#pragma region ForwardDeclarations
class UCameraComponent;
class USpringArmComponent;
#pragma endregion ForwardDeclarations

/**
 * Base class for player character
 */
UCLASS()
class BUSYCHEF_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
#pragma region Properties
protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
#pragma endregion

#pragma region Methods
public:

	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Death() override;

protected:

	virtual void OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext) override;

private:

	void MovementX(float Value);
	void MovementY(float Value);
	void MouseX(float Value);
	void MouseY(float Value);

	// Rotates player towards mouse point
	void PlayerAim();

	void NextWeapon();
	void PreviousWeapon();
#pragma endregion
};
