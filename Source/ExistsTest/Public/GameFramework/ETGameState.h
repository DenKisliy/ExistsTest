// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "../Subsystem/ETSessionSubsystem.h"
#include "../../ExistsTestGameMode.h"
#include "ETHUD.h"
#include "../../ExistsTestCharacter.h"
#include "ETPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "ETGameState.generated.h"

/**
 * 
 */
UCLASS()
class EXISTSTEST_API AETGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	int TimerInterval;

	int TimerCounter;

	FTimerHandle TimerHandle;

	UPROPERTY(ReplicatedUsing = OnRep_TimeChecker)
	int TimeChecker;

	int CountOfDeadCharacter = 0;

public:
	void StartBeginPlayTimer();

	UFUNCTION()
	void OnTimerCounter();

	UFUNCTION(Server, Reliable)
	void StartSession();

	UFUNCTION(Server, Reliable)
	void DestroySession();

	UFUNCTION()
	void CharacterDead();

protected:
	virtual void AddPlayerState(APlayerState* PlayerState) override;

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

private:
	int GetPlayerCountFromGameMode();

	int GetTimeForBeginMatch();

	UFUNCTION()
	void OnRep_TimeChecker();

	void SetTimeForPlayers();
};
