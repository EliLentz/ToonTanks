// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor) {
	if (DeadActor == Tank) {
		Tank->HandleDestruction();
		if (PlayerController)
			PlayerController->SetPlayerEnabledState(false);

		GameOver(false);
	}
	else if (auto destroyedTower = Cast<ATower>(DeadActor)) {
		destroyedTower->HandleDestruction();

		--TargetTowers;

		if (TargetTowers == 0) GameOver(true);
	}
}

void AToonTanksGameMode::BeginPlay() {
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart() {
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (PlayerController) {
		PlayerController->SetPlayerEnabledState(false);

		FTimerHandle Timer;
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(PlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(Timer, TimerDelegate, StartDelay, false);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount() {
	TArray<AActor*> towers;

	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);

	return towers.Num();
}