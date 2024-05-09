// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExistsTestGameMode.h"
#include "ExistsTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

void AExistsTestGameMode::BeginPlay()
{
	Super::BeginPlay();

	UETGameInstance* gameInstance = Cast<UETGameInstance>(GetGameInstance());
	if (gameInstance)
	{
		if (gameInstance->IsConnectToSession() && IsValid(PickupManagerClass))
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.Instigator = GetInstigator();
			SpawnInfo.ObjectFlags |= RF_Transient;	
			PickupManager = GetWorld()->SpawnActor<AETPickupManager>(PickupManagerClass, SpawnInfo);
		}
	}
}

void AExistsTestGameMode::StartSpawnHealthBox()
{
	if (IsValid(PickupManager))
	{
		PickupManager->StartSpawnHealthPacks();
	}
}
