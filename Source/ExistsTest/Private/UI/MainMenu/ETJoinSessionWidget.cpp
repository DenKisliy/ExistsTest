// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/ETJoinSessionWidget.h"

void UETJoinSessionWidget::CreateButton(FOnlineSessionSearchResult SessionInfo)
{
	Session = SessionInfo;
	FString SessionName = "UMSessionButton";
	Session.Session.SessionSettings.Get(FName("SESSION_NAME_KEY"), SessionName);

	FString TextOfButton = (Session.Session.SessionSettings.bIsDedicated ? "Server:" : "Player:") + SessionName;
	SessionName.RemoveSpacesInline();

	UButton* button = NewObject<UButton>(this, UButton::StaticClass());

	UTextBlock* TextBlockOfButton = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	TextBlockOfButton->SetText(FText::FromString(TextOfButton));

	UScaleBox* buttonTextScaleBox = NewObject<UScaleBox>(this, UScaleBox::StaticClass());
	buttonTextScaleBox->SetStretch(EStretch::ScaleToFill);

	USizeBox* buttonTextSizeBox = NewObject<USizeBox>(this, USizeBox::StaticClass());
	buttonTextSizeBox->SetMinDesiredWidth(200.0f);
	buttonTextSizeBox->SetMinDesiredHeight(40.0f);
	buttonTextSizeBox->AddChild(TextBlockOfButton);
	buttonTextScaleBox->AddChild(buttonTextSizeBox);

	button->AddChild(buttonTextScaleBox);

	button->OnClicked.AddDynamic(this, &UETJoinSessionWidget::OnClickButton);

	Border->AddChild(button);
}

void UETJoinSessionWidget::OnClickButton()
{
	UETSessionSubsystem* sessionManager = GetGameInstance()->GetSubsystem<UETSessionSubsystem>();

	if (sessionManager)
	{
		FString SessionName = "";
		Session.Session.SessionSettings.Get(FName("SESSION_NAME_KEY"), SessionName);

		sessionManager->JoinToSession(FName(*SessionName), Session);
	}
}
