// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Public/Manager/ETPickupManager.h"

#include "ExistsTestGameMode.generated.h"

UCLASS(minimalapi)
class AExistsTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Varible")
	FString OpenLevelURL = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Varible")
	int CountOfMaxNumPlayers = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State Varible")
	int TimeForBeginMatch = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<AETPickupManager> PickupManagerClass;

private:
	AETPickupManager* PickupManager;

protected:
	virtual void BeginPlay() override;

public:
	void StartSpawnHealthBox();
};



