// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/ETGameInstance.h"

void UETGameInstance::SetConnectToSession(bool Value)
{
	bConnectToSession = Value;
}

bool UETGameInstance::IsConnectToSession()
{
	return bConnectToSession;
}

void UETGameInstance::UpdateGameRating(FString Name)
{
	bool bFind = false;

	for (FPlayerScore* elem : GameRating)
	{
		if (elem->PlayerName == Name)
		{
			bFind = true;
			elem->UpdateScore();
			break;
		}
	}

	if (!bFind)
	{
		FPlayerScore* newElement = new FPlayerScore(Name);
		GameRating.Add(newElement);
	}

	GameRating.Sort([](const FPlayerScore& Lhs, const FPlayerScore& Rhs) {
		return Lhs.Score > Rhs.Score;
		});
}

TArray<FPlayerScore*> UETGameInstance::GetGameRating()
{
	return GameRating;
}

void UETGameInstance::ClearGameRating()
{
	GameRating.Empty();
}
