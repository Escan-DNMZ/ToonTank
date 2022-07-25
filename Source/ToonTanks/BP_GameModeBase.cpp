// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "ToonTanksPlayerController.h"
#include "GameFramework/GameMode.h"

void ABP_GameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDesruction();
		if (ToonTankPlayerController)
		{
			ToonTankPlayerController->SetPlayerEnableState(false);

			
		}
		GameOver(false);
		
	}
	else if (ATurret*  DestroyedTower = Cast<ATurret>(DeadActor)){
		DestroyedTower->HandleDestruction();
		--TargetTowers;
		if (TargetTowers == 0)
		{
			GameOver(true);
		
		}
	}
}
void ABP_GameModeBase::BeginPlay() {
	Super::BeginPlay();

	HandleGameStart();



}
void ABP_GameModeBase::HandleGameStart() {

	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	StartGame();

	if (ToonTankPlayerController)
	{
		ToonTankPlayerController->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTankPlayerController,
			&AToonTanksPlayerController::SetPlayerEnableState,
			true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false);


	}
}

int32 ABP_GameModeBase::GetTargetTowerCount() {
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this,ATurret::StaticClass(),Towers);
	return Towers.Num();
}