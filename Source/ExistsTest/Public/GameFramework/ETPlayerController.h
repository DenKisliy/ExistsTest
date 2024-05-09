// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "ETGameInstance.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"

#include "ETPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EXISTSTEST_API AETPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Server, Reliable)
	void SpawnCharacter();

	UFUNCTION(Client, Reliable)
	void UpdateGameRatingForEachPlayers(const FString& PlayerName);
	
	UFUNCTION(Client, Reliable)
	void UpdateGameInstance();

};
