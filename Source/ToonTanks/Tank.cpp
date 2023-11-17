// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATank::ATank() {
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay() {
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

APlayerController* ATank::GetPlayerController() const {
	return PlayerController;
}

void ATank::HandleDestruction() {
	Super::HandleDestruction();
	bAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::SetCanFire(bool Value) {
	CanFire = Value;
}

void ATank::Shoot(const FInputActionValue& Value) {
	const bool value = Value.Get<bool>();


	if (GetController() && value)
	{
		if (CanFire) {
			Fire();
			SetCanFire(false);
			FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(this, &ATank::SetCanFire, true);
			GetWorldTimerManager().SetTimer(FireRateTimerHandle, timerDelegate, TimeToReload, false);
		}
		else UE_LOG(LogTemp, Warning, TEXT("Reloading..."));
	}
}

void ATank::BaseMove(const FInputActionValue& Value) {
	const float value = Value.Get<float>();


	if (GetController() && value != 0) {
		FVector forwardVector(0.f);
		forwardVector.X += value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);

		AddActorLocalOffset(forwardVector, true);
	}
}

void ATank::BaseRotate(const FInputActionValue& Value) {
	const float value = Value.Get<float>();

	if (GetController() && value != 0) {
		FRotator rotation(0.f);
		rotation.Yaw += value * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

		AddActorLocalRotation(rotation);
	}
}

void ATank::TurretRotate(const FInputActionValue& Value) {
	const float value = Value.Get<float>();

	if (GetController() && value != 0) {
		SetTurretRotation(value * TurretRotationSpeed);

		FRotator newRotation = FRotator(SpringArm->GetComponentRotation());
		newRotation.Yaw += value * TurretRotationSpeed;

		SpringArm->SetWorldRotation(newRotation);
	}
}

void ATank::CameraDistance(const FInputActionValue& Value) {
	const float value = Value.Get<float>();

	if (GetController() && value != 0) {

		float valueAfterChange = ATank::SpringArm->TargetArmLength + value * CameraDistanceSpeed;

		if (valueAfterChange > MaxCameraDistance ||
			valueAfterChange < MinCameraDistance) {
			return;
		}

		SpringArm->TargetArmLength = valueAfterChange;
	}
}

void ATank::CameraAngle(const FInputActionValue& Value) {
	const float value = Value.Get<float>();

	if (GetController() && value != 0) {

		FRotator valueAfterChange = FRotator(SpringArm->GetComponentRotation());
		valueAfterChange.Pitch += value * CameraAngleSpeed;

		if (valueAfterChange.Pitch > MaxCameraAngle ||
			valueAfterChange.Pitch < MinCameraAngle) {
			return;
		}

		SpringArm->SetWorldRotation(valueAfterChange);
	}
}

void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ATank::Shoot);
		EnhancedInputComponent->BindAction(BaseMoveAction, ETriggerEvent::Triggered, this, &ATank::BaseMove);
		EnhancedInputComponent->BindAction(BaseRotateAction, ETriggerEvent::Triggered, this, &ATank::BaseRotate);
		EnhancedInputComponent->BindAction(TurretRotateAction, ETriggerEvent::Triggered, this, &ATank::TurretRotate);
		EnhancedInputComponent->BindAction(CameraDistanceAction, ETriggerEvent::Triggered, this, &ATank::CameraDistance);
		EnhancedInputComponent->BindAction(CameraAngleAction, ETriggerEvent::Triggered, this, &ATank::CameraAngle);
	}
}