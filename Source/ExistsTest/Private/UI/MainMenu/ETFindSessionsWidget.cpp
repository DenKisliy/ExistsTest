// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/ETFindSessionsWidget.h"

void UETFindSessionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UETSessionSubsystem* sessionManager = GetGameInstance()->GetSubsystem<UETSessionSubsystem>();

	if (sessionManager)
	{
		sessionManager->ResultOfFindSessionsDelegate.AddDynamic(this, &UETFindSessionsWidget::CreateButtonForFindSession);
	}
}

void UETFindSessionsWidget::CreateButtonForFindSession(bool bFindSession)
{
	VerticalBox->ClearChildren();

	if (bFindSession && IsValid(JoinSessionWidget))
	{
		UETSessionSubsystem* sessionManager = GetGameInstance()->GetSubsystem<UETSessionSubsystem>();

		if (sessionManager)
		{
			for (FOnlineSessionSearchResult Result : sessionManager->GetFindSessions())
			{
				UETJoinSessionWidget* button = CreateWidget<UETJoinSessionWidget>(this, JoinSessionWidget);
				button->CreateButton(Result);

				VerticalBox->AddChild(button);
			}
		}
	}
	else
	{
		ShowInfoText("Can not find any session");
	}
}

void UETFindSessionsWidget::ShowInfoText(FString InfoText)
{
	VerticalBox->ClearChildren();

	UTextBlock* TextBlockOfButton = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	TextBlockOfButton->SetText(FText::FromString(InfoText));

	UScaleBox* buttonTextScaleBox = NewObject<UScaleBox>(this, UScaleBox::StaticClass());
	buttonTextScaleBox->SetStretch(EStretch::ScaleToFill);

	USizeBox* buttonTextSizeBox = NewObject<USizeBox>(this, USizeBox::StaticClass());
	buttonTextSizeBox->SetMinDesiredWidth(200.0f);
	buttonTextSizeBox->SetMinDesiredHeight(40.0f);
	buttonTextSizeBox->AddChild(TextBlockOfButton);
	buttonTextScaleBox->AddChild(buttonTextSizeBox);
	VerticalBox->AddChild(buttonTextScaleBox);
}
