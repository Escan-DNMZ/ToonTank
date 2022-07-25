// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BP_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ABP_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	virtual void PawnKilled(APawn* PawnKilled);

	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTankPlayerController;

	float StartDelay= 3.f;

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();

	void HandleGameStart();
};
