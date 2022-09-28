// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
}

void APlayerCharacter::Tick(float DeltaTime) {
	PlayerAim();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MovementX", this, &APlayerCharacter::MovementX);
	PlayerInputComponent->BindAxis("MovementY", this, &APlayerCharacter::MovementY);
}

void APlayerCharacter::MovementX(float Value) {
	if ((Controller != NULL) && (Value != 0.0f)) {
		AddMovementInput(FVector(Value, 0, 0));
	}
}

void APlayerCharacter::MovementY(float Value) {
	if ((Controller != NULL) && (Value != 0.0f)) {
		AddMovementInput(FVector(0, Value, 0));
	}
}

void APlayerCharacter::PlayerAim() {
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		FVector WorldLocation;
		FVector WorldDirection;
		PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

		FPlane GroundPlane = FPlane(FVector(0), FVector(0, 0, 1));
		const FVector AimPoint = FMath::RayPlaneIntersection(WorldLocation, WorldDirection, GroundPlane);

		FRotator NewRotation = FRotationMatrix::MakeFromX(AimPoint - GetActorLocation()).Rotator();

		FRotator CurrentRotation = GetActorRotation();
		CurrentRotation.Yaw = NewRotation.Yaw;
		SetActorRotation(CurrentRotation);
	}
}
