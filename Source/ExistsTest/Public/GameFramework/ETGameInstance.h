// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ETGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerScore
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite)
	int Score;

	FPlayerScore()
	{
		PlayerName = "";
		Score = 0;
	}

	FPlayerScore(FString NewName)
	{
		PlayerName = NewName;
		Score = 1;
	}

	void UpdateScore()
	{
		Score = Score + 1;
	}
};

UCLASS()
class EXISTSTEST_API UETGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	bool bConnectToSession = false;

	TArray<FPlayerScore*> GameRating;

public:
	void SetConnectToSession(bool Value);

	UFUNCTION(BlueprintCallable)
	bool IsConnectToSession();

	void UpdateGameRating(FString Name);

	TArray<FPlayerScore*> GetGameRating();

	void ClearGameRating();
};
