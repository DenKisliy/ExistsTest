// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/ETGameState.h"

void AETGameState::StartBeginPlayTimer()
{
	TimerInterval = 1.0f;
	TimerCounter = GetTimeForBeginMatch() + 1;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AETGameState::OnTimerCounter, TimerInterval, true);
}

void AETGameState::OnTimerCounter()
{
	TimerCounter = TimerCounter - 1;

	TimeChecker = TimerCounter;

	SetTimeForPlayers();

	if (TimeChecker == GetTimeForBeginMatch())
	{
		StartSession();
	}
}

void AETGameState::StartSession_Implementation()
{
	UETSessionSubsystem* sessionManager = GetGameInstance()->GetSubsystem<UETSessionSubsystem>();

	if (sessionManager)
	{
		sessionManager->StartSession();
	}
}

void AETGameState::DestroySession_Implementation()
{
	for (APlayerState* playerState : PlayerArray)
	{
		if (AETPlayerController* playerController = Cast<AETPlayerController>(playerState->GetOwningController()))
		{
			playerController->UpdateGameInstance();
		}
	}

	UETSessionSubsystem* sessionManager = GetGameInstance()->GetSubsystem<UETSessionSubsystem>();

	if (sessionManager)
	{
		sessionManager->DestroySession();
	}
}

void AETGameState::CharacterDead()
{
	CountOfDeadCharacter = CountOfDeadCharacter + 1;

	if (CountOfDeadCharacter == GetPlayerCountFromGameMode())
	{
		DestroySession();
	}
}

void AETGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	if (PlayerArray.Num() == GetPlayerCountFromGameMode())
	{
		StartBeginPlayTimer();
	}
}

void AETGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AETGameState, TimeChecker);
}

int AETGameState::GetPlayerCountFromGameMode()
{
	if (UGameplayStatics::GetGameMode(GetWorld()))
	{
		AExistsTestGameMode* gameMode = Cast<AExistsTestGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (gameMode)
		{
			return gameMode->CountOfMaxNumPlayers;
		}
	}

	return 0;
}

int AETGameState::GetTimeForBeginMatch()
{
	if (UGameplayStatics::GetGameMode(GetWorld()))
	{
		AExistsTestGameMode* gameMode = Cast<AExistsTestGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (gameMode)
		{
			return gameMode->TimeForBeginMatch;
		}
	}

	return 0;
}

void AETGameState::OnRep_TimeChecker()
{
	if (TimerCounter != TimeChecker)
	{
		TimerCounter = TimeChecker;

		SetTimeForPlayers();
	}
}

void AETGameState::SetTimeForPlayers()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	if (TimerCounter != -1)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AETGameState::OnTimerCounter, TimerInterval, true);
	}

	if (IsValid(GetWorld()->GetFirstPlayerController()))
	{
		APlayerController* playerController = GetWorld()->GetFirstPlayerController();

		if (IsValid(playerController->GetHUD()))
		{
			AETHUD* playerHUD = Cast<AETHUD>(playerController->GetHUD());

			if (IsValid(playerHUD))
			{
				playerHUD->SetTimeForTimerWidget(TimerCounter);
			}

			if (TimerCounter == -1)
			{
				if (UGameplayStatics::GetGameMode(GetWorld()))
				{
					AExistsTestGameMode* gameMode = Cast<AExistsTestGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
					if (gameMode)
					{
						gameMode->StartSpawnHealthBox();
					}
				}

				for (APlayerState* playerState : PlayerArray)
				{
					if (AExistsTestCharacter* character = Cast<AExistsTestCharacter>(playerState->GetPawn()))
					{
						character->LaunchDamageEffect();
						GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
						GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
						character->CharacterDeadDelefate.AddDynamic(this, &AETGameState::CharacterDead);
					}
				}
			}
		}
	}
}
