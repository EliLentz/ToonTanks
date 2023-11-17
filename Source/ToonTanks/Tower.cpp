// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange()) {
		ABasePawn::SetTurretRotation(Tank->GetActorLocation(), DeltaTime, TurretRotationSpeed);
	}
}

void ATower::CheckFireCondition() {
	if (InFireRange() && Tank->bAlive) {
		Fire();
	}
}

bool ATower::InFireRange() {
	return Tank && FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
}

void ATower::HandleDestruction() {
	Super::HandleDestruction();
	Destroy();
}