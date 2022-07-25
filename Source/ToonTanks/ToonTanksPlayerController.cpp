// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"


void AToonTanksPlayerController::SetPlayerEnableState(bool bPlayerEnabled) {
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
		GetPawn()->SetActorHiddenInGame(false);
	}
	else {
		GetPawn()->DisableInput(this);
		GetPawn()->SetActorHiddenInGame(true);
	}
	bShowMouseCursor = bPlayerEnabled;
}
