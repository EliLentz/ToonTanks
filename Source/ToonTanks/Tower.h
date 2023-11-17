// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

private:
	class ATank* Tank;
	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float FireRate = 1.5f;
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float FireRange = 800.f;
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float TurretRotationSpeed = 5.f;

	void CheckFireCondition();
	bool InFireRange();
};
