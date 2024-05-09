// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "../AdditionalItems/ETHealthPacksActor.h"

#include "ETPickupManager.generated.h"

UCLASS()
class EXISTSTEST_API AETPickupManager : public AActor
{
	GENERATED_BODY()
	
private:
	TArray<AActor*> HealthPacksArray;

	int LastCheckHealthPackIndex = -1;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<AETHealthPacksActor> HealthPackClass;

public:	
	// Sets default values for this actor's properties
	AETPickupManager();

	UFUNCTION()
	void AddNewHealthPack();

	void StartSpawnHealthPacks();

private:
	void FindAllHealthPacks();
};
