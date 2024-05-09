// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ETPickupManager.h"

// Sets default values
AETPickupManager::AETPickupManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AETPickupManager::AddNewHealthPack()
{
	int newHealthPacIndex = FMath::RandRange(1, HealthPacksArray.Num());
	if (LastCheckHealthPackIndex == newHealthPacIndex)
	{
		do
		{
			newHealthPacIndex = FMath::RandRange(1, HealthPacksArray.Num());
		} while (newHealthPacIndex == LastCheckHealthPackIndex);
	}

	if (AETHealthPacksActor* healthPack = Cast<AETHealthPacksActor>(HealthPacksArray[newHealthPacIndex - 1]))
	{
		healthPack->AddHealthBox();
		LastCheckHealthPackIndex = newHealthPacIndex;
	}
}

void AETPickupManager::StartSpawnHealthPacks()
{
	LastCheckHealthPackIndex = -1;
	FindAllHealthPacks();
}

void AETPickupManager::FindAllHealthPacks()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), HealthPackClass, HealthPacksArray);

	if (HealthPacksArray.Num() > 0)
	{
		for (AActor* pack : HealthPacksArray)
		{
			if (AETHealthPacksActor* healthPack = Cast<AETHealthPacksActor>(pack))
			{
				healthPack->TakeHealthPackDelegate.AddDynamic(this, &AETPickupManager::AddNewHealthPack);
			}
		}

		AddNewHealthPack();
	}
}

