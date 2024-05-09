// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/ETPlayerController.h"

void AETPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (UETGameInstance* gameInstance = Cast<UETGameInstance>(GetGameInstance()))
		{
			if (gameInstance->IsConnectToSession())
			{
				SpawnCharacter();
			}
		}
	}
}

void AETPlayerController::UpdateGameInstance_Implementation()
{
	if (UETGameInstance* gameInstance = Cast<UETGameInstance>(GetGameInstance()))
	{
		gameInstance->SetConnectToSession(false);
	}
}

void AETPlayerController::UpdateGameRatingForEachPlayers_Implementation(const FString& PlayerName)
{
	if (UETGameInstance* gameInstance = Cast<UETGameInstance>(GetGameInstance()))
	{
		gameInstance->UpdateGameRating(PlayerName);
	}
}

void AETPlayerController::SpawnCharacter_Implementation()
{
	if (IsValid(GetPawn()))
	{
		GetPawn()->Destroy();
	}

	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}
