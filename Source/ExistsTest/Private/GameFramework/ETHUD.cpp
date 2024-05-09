// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/ETHUD.h"

void AETHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UETGameInstance* gameInstance = Cast<UETGameInstance>(GetGameInstance()))
	{
		if (!gameInstance->IsConnectToSession())
		{
			if (IsValid(MainMenuStatic))
			{
				GetOwningPlayerController()->SetShowMouseCursor(true);
				GetOwningPlayerController()->SetInputMode(FInputModeUIOnly());

				UETMainMenuWidget* mainMenuWidget = CreateWidget<UETMainMenuWidget>(this->GetOwningPlayerController(), MainMenuStatic);
				mainMenuWidget->AddToViewport();
			}
		}
		else
		{
			if (IsValid(TimerStatic))
			{
				TimerWidget = CreateWidget<UETTimerWidget>(this->GetOwningPlayerController(), TimerStatic);
				TimerWidget->SetAnchorsInViewport(FAnchors(0.5f, 0.0f));
				TimerWidget->SetAlignmentInViewport(FVector2D(double(0.5), 0));
				TimerWidget->SetTime(0);
				TimerWidget->AddToViewport();
			}

			if (IsValid(AttributeStatic))
			{
				AttributeWidget = CreateWidget<UETAttributeWidget>(this->GetOwningPlayerController(), AttributeStatic);
				AttributeWidget->SetStartData();
				AttributeWidget->AddToViewport();
			}
		}

		if (IsValid(ResultGameStatic) && gameInstance->GetGameRating().Num() > 0)
		{
			UETResultGameWidget* resultGameWidget = CreateWidget<UETResultGameWidget>(this->GetOwningPlayerController(), ResultGameStatic);
			resultGameWidget->ShowResultOfGame();
			resultGameWidget->AddToViewport(5);
		}
	}
}

void AETHUD::SetTimeForTimerWidget(int Time)
{
	if (IsValid(TimerWidget))
	{
		TimerWidget->SetTime(Time);
	}
}

void AETHUD::SetValueForAttribute(float Value)
{
	if (IsValid(AttributeWidget))
	{
		AttributeWidget->SetPercent(Value);
	}
}
