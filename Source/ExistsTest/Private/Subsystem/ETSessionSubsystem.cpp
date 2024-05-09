// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ETSessionSubsystem.h"

void UETSessionSubsystem::Deinitialize()
{
	DestroySession();

	Super::Deinitialize();
}

void UETSessionSubsystem::SetSessionInfoFromGameMode()
{
	if (OpenLevelURL.IsEmpty())
	{
		if (UGameplayStatics::GetGameMode(GetWorld()))
		{
			AExistsTestGameMode* gameMode = Cast<AExistsTestGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			if (gameMode)
			{
				OpenLevelURL = gameMode->OpenLevelURL;
				CountOfMaxNumPlayers = gameMode->CountOfMaxNumPlayers;
			}
		}
	}
}

TArray<FOnlineSessionSearchResult> UETSessionSubsystem::GetFindSessions()
{
	return ArrayOfFindSessions;
}

void UETSessionSubsystem::StartSession()
{
	IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
	if (onlineSub)
	{
		IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();
		if (sessionsPtrRef)
		{
			sessionsPtrRef->OnStartSessionCompleteDelegates.AddUObject(this, &UETSessionSubsystem::OnStartSessionComplete);
			sessionsPtrRef->StartSession(GameSessionName);
		}
	}
}

void UETSessionSubsystem::EndSession()
{
	IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
	if (onlineSub)
	{
		IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();
		if (sessionsPtrRef)
		{
			sessionsPtrRef->OnEndSessionCompleteDelegates.AddUObject(this, &UETSessionSubsystem::OnEndSessionCompleted);
			sessionsPtrRef->EndSession(GameSessionName);
		}
	}
}

void UETSessionSubsystem::CreateSession(FName SessionName, bool bIsLAN, bool bIsDedicatedServer)
{
	IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
	if (onlineSub)
	{
		IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();
		if (sessionsPtrRef)
		{
			SetSessionInfoFromGameMode();

			FOnlineSessionSettings sessionSettings;
			sessionSettings.bIsDedicated = bIsDedicatedServer;
			sessionSettings.bAllowInvites = true;
			sessionSettings.bIsLANMatch = bIsLAN;
			sessionSettings.NumPublicConnections = CountOfMaxNumPlayers > 0 ? CountOfMaxNumPlayers : 2;
			sessionSettings.bUseLobbiesIfAvailable = false;
			sessionSettings.bUsesPresence = false;
			sessionSettings.bShouldAdvertise = true;
			sessionSettings.Set(FName("SESSION_NAME_KEY"), SessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineService);

			sessionsPtrRef->OnCreateSessionCompleteDelegates.AddUObject(this, &UETSessionSubsystem::OnCreateSessionComplete);
			
			const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			sessionsPtrRef->CreateSession(*localPlayer->GetPreferredUniqueNetId(), SessionName, sessionSettings);
		}
	}
}

void UETSessionSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
		if (onlineSub)
		{
			IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();
			if (sessionsPtrRef)
			{
				if (UETGameInstance* gameInstance = Cast<UETGameInstance>(GetGameInstance()))
				{
					gameInstance->SetConnectToSession(bWasSuccessful);
					GameSessionName = SessionName;
					sessionsPtrRef->OnCreateSessionCompleteDelegates.Clear();
					GetWorld()->ServerTravel(OpenLevelURL);
				}
			}
		}
	}

}

void UETSessionSubsystem::DestroySession()
{
	if (!GameSessionName.ToString().IsEmpty())
	{
		IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
		if (onlineSub)
		{
			IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();
			if (sessionsPtrRef)
			{
				sessionsPtrRef->OnDestroySessionCompleteDelegates.AddUObject(this, &UETSessionSubsystem::OnDestroySessionComplete);
				if (!GameSessionName.ToString().IsEmpty() && GameSessionName != "None")
				{
					sessionsPtrRef->DestroySession(GameSessionName);
				}
			}
		}
	}
}

void UETSessionSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
		if (onlineSub)
		{
			IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();
			if (sessionsPtrRef)
			{
				sessionsPtrRef->OnDestroySessionCompleteDelegates.Clear();
				GameSessionName = "";
				UGameplayStatics::OpenLevel(GetWorld(), "MainMenuMap", true);
			}
		}
	}
}

void UETSessionSubsystem::FindSessions()
{
	IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
	if (onlineSub)
	{
		IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();
		if (sessionsPtrRef)
		{
			SessionSearch.Reset();
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, false, EOnlineComparisonOp::Equals);
			SessionSearch->MaxSearchResults = 20;
			SessionSearch->bIsLanQuery = true;

			sessionsPtrRef->OnFindSessionsCompleteDelegates.AddUObject(this, &UETSessionSubsystem::OnFindSessionsComplete);

			const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();

			sessionsPtrRef->FindSessions(*localPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
		}
	}
}

void UETSessionSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
	ArrayOfFindSessions.Empty();

	if (bWasSuccessful)
	{
		IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
		if (onlineSub)
		{
			IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();
			if (sessionsPtrRef)
			{
				sessionsPtrRef->OnFindSessionsCompleteDelegates.Clear();
				for (FOnlineSessionSearchResult Result : SessionSearch->SearchResults)
				{
					if (Result.IsValid())
					{
						ArrayOfFindSessions.Add(Result);
					}
				}

				ResultOfFindSessionsDelegate.Broadcast(SessionSearch->SearchResults.Num() > 0);
			}
		}
	}
}

void UETSessionSubsystem::JoinToSession(FName SessionName, const FOnlineSessionSearchResult& SearchResult)
{
	IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
	if (onlineSub)
	{
		IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();

		if (sessionsPtrRef)
		{
			sessionsPtrRef->OnJoinSessionCompleteDelegates.AddUObject(this, &UETSessionSubsystem::OnJoinSessionComplete);

			const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			sessionsPtrRef->JoinSession(*localPlayer->GetPreferredUniqueNetId(), SessionName, SearchResult);
		}
	}
}

void UETSessionSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		APlayerController* playerController = GetWorld()->GetFirstPlayerController();

		if (playerController)
		{
			IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
			if (onlineSub)
			{
				IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();

				if (sessionsPtrRef)
				{
					FString joinAdress;
					sessionsPtrRef->GetResolvedConnectString(SessionName, joinAdress);

					if (!joinAdress.IsEmpty())
					{
						if (UETGameInstance* gameInstance = Cast<UETGameInstance>(GetGameInstance()))
						{
							gameInstance->SetConnectToSession(Result == EOnJoinSessionCompleteResult::Success);
							GameSessionName = SessionName;
							sessionsPtrRef->OnJoinSessionCompleteDelegates.Clear();
							playerController->ClientTravel(joinAdress, ETravelType::TRAVEL_Absolute);
						}
					}
				}
			}
		}
	}
}

void UETSessionSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
		if (onlineSub)
		{
			IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();

			if (sessionsPtrRef)
			{
				sessionsPtrRef->OnStartSessionCompleteDelegates.Clear();
			}
		}
	}
}

void UETSessionSubsystem::OnEndSessionCompleted(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		IOnlineSubsystem* onlineSub = Online::GetSubsystem(GetWorld());
		if (onlineSub)
		{
			IOnlineSessionPtr sessionsPtrRef = onlineSub->GetSessionInterface();

			if (sessionsPtrRef)
			{
				sessionsPtrRef->OnEndSessionCompleteDelegates.Clear();
				if (!GameSessionName.ToString().IsEmpty())
				{
					DestroySession();
				}
			}
		}
	}
}
