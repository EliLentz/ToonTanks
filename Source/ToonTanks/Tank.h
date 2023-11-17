// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	bool bAlive = true;

	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	APlayerController* GetPlayerController() const;
	void SetCanFire(bool Value);
	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	void BeginPlay();

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotationSpeed = 90.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TurretRotationSpeed = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float CameraDistanceSpeed = 25.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float MaxCameraDistance = 1300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float MinCameraDistance = 450.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float CameraAngleSpeed = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float MaxCameraAngle = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float MinCameraAngle = -60.f;

	UPROPERTY(VisibleAnywhere, Category = "Component", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Component", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;
	UPROPERTY(EditAnywhere, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInputAction* BaseMoveAction;
	UPROPERTY(EditAnywhere, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInputAction* BaseRotateAction;
	UPROPERTY(EditAnywhere, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TurretRotateAction;
	UPROPERTY(EditAnywhere, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CameraDistanceAction;
	UPROPERTY(EditAnywhere, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CameraAngleAction;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float TimeToReload = 2.f;

	FTimerHandle FireRateTimerHandle;
	bool CanFire = true;

	UPROPERTY()
	APlayerController* PlayerController;

	void Shoot(const FInputActionValue& Value);
	void BaseMove(const FInputActionValue& Value);
	void BaseRotate(const FInputActionValue& Value);
	void TurretRotate(const FInputActionValue& Value);
	void CameraDistance(const FInputActionValue& Value);
	void CameraAngle(const FInputActionValue& Value);
};
