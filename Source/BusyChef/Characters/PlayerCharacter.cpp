// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "../Components/CharacterStatsComponent.h"
#include "../Components/WeaponComponent.h"
#include "../Utilities/GameContextFunctionLibrary.h"

APlayerCharacter::APlayerCharacter() {
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bDoCollisionTest = false;

	// TODO make camera ignore objects

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;

	Tags.Add("Player");
}

void APlayerCharacter::Tick(float DeltaTime) {
	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MovementX", this, &APlayerCharacter::MovementX);
	PlayerInputComponent->BindAxis("MovementY", this, &APlayerCharacter::MovementY);
	PlayerInputComponent->BindAxis("MouseX", this, &APlayerCharacter::MouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &APlayerCharacter::MouseY);

	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ACharacterBase::AttackStart);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &ACharacterBase::AttackStop);
	PlayerInputComponent->BindAction("NextWeapon", EInputEvent::IE_Pressed, this, &APlayerCharacter::NextWeapon);
	PlayerInputComponent->BindAction("PreviousWeapon", EInputEvent::IE_Pressed, this, &APlayerCharacter::PreviousWeapon);
}

void APlayerCharacter::Death() {
	AttackStop();

	if (UGameContextFunctionLibrary::GetGameContext(this) == EGameContext::Game) {
		UGameContextFunctionLibrary::GameOver(this);
	}
}

void APlayerCharacter::OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext) {
	if (NewContext == EGameContext::Game) {
		if (StatsComponent != nullptr) {
			StatsComponent->InitStats();
		}
	} // TODO Handle other contexts
}

void APlayerCharacter::MovementX(float Value) {
	if ((Controller != NULL) && (Value != 0.0f)) {
		AddMovementInput(FollowCamera->GetRightVector().RotateAngleAxis(-90.0f, FVector::UpVector), Value);
	}
}

void APlayerCharacter::MovementY(float Value) {
	if ((Controller != NULL) && (Value != 0.0f)) {
		AddMovementInput(FollowCamera->GetRightVector(), Value);
	}
}

void APlayerCharacter::MouseX(float Value) {
	if ((Controller != NULL) && (Value != 0.0f)) {
		PlayerAim();
	}
}

void APlayerCharacter::MouseY(float Value) {
	if ((Controller != NULL) && (Value != 0.0f)) {
		PlayerAim();
	}
}

void APlayerCharacter::PlayerAim() {
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		FVector WorldLocation;
		FVector WorldDirection;
		PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

		FVector Ground = GetActorLocation();

		FPlane GroundPlane = FPlane(Ground, FVector(0, 0, 1));
		const FVector AimPoint = FMath::RayPlaneIntersection(WorldLocation, WorldDirection, GroundPlane);

		FRotator NewRotation = FRotationMatrix::MakeFromX(AimPoint - Ground).Rotator();

		FRotator CurrentRotation = GetActorRotation();
		CurrentRotation.Yaw = NewRotation.Yaw;
		SetActorRotation(CurrentRotation);
	}
}

void APlayerCharacter::NextWeapon() {
	if (WeaponComponent != nullptr) {
		WeaponComponent->NextWeapon();
	}
}

void APlayerCharacter::PreviousWeapon() {
	if (WeaponComponent != nullptr) {
		WeaponComponent->PreviousWeapon();
	}
}
