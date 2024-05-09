// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/ETMainMenuWidget.h"

void UETMainMenuWidget::NativeConstruct()
{
	VerticalBox->ClearChildren();

	CreateButton("Create session", CreateDelegate(this, "CreateSession"));
	CreateButton("Find session", CreateDelegate(this, "FindSessions"));
	if (IsValid(FindSessionsWidget))
	{
		FindSessionResultWidget = CreateWidget<UETFindSessionsWidget>(this, FindSessionsWidget);
		VerticalBox->AddChild(FindSessionResultWidget);
	}

}

void UETMainMenuWidget::CreateButton(FString NameOfButton, FScriptDelegate ClickDelegate)
{
	FString TextOfButton = NameOfButton;
	NameOfButton.RemoveSpacesInline();

	UButton* button = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), FName(*NameOfButton));

	button->OnClicked.Add(ClickDelegate);

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

	VerticalBox->AddChild(button);
}

FScriptDelegate UETMainMenuWidget::CreateDelegate(UObject* Object, FString FunctionName)
{
	if (!(FunctionName.IsEmpty()) && Object)
	{
		FScriptDelegate Delegate;
		Delegate.BindUFunction(this, FName(*FunctionName));
		return Delegate;
	}
	else
	{
		return FScriptDelegate();
	}
}

void UETMainMenuWidget::CreateSession()
{
	UETSessionSubsystem* sessionManager = GetGameInstance()->GetSubsystem<UETSessionSubsystem>();

	if (sessionManager)
	{
		sessionManager->CreateSession(FName(*GetOwningPlayerState()->GetPlayerName()), true, false);
	}
}

void UETMainMenuWidget::FindSessions()
{
	UETSessionSubsystem* sessionManager = GetGameInstance()->GetSubsystem<UETSessionSubsystem>();

	if (sessionManager)
	{
		if (FindSessionResultWidget)
		{
			FindSessionResultWidget->ShowInfoText("Search sessions");
		}
		sessionManager->FindSessions();
	}
}
