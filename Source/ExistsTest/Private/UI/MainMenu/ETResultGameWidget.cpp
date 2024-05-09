// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/ETResultGameWidget.h"

void UETResultGameWidget::ShowResultOfGame()
{
	if (IsValid(ResultGameVerticalBox))
	{
		if (UETGameInstance* gameInstance = Cast<UETGameInstance>(GetGameInstance()))
		{
			TArray<FPlayerScore*> gameRating = gameInstance->GetGameRating();
			for (int i = 0;  i< gameRating.Num(); i++)
			{
				FString text = FString::FromInt(i + 1) + " : " + gameRating[i]->PlayerName + " : " + FString::FromInt(gameRating[i]->Score);
				UTextBlock* textBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
				textBlock->SetText(FText::FromString(text));

				UScaleBox* textScaleBox = NewObject<UScaleBox>(this, UScaleBox::StaticClass());
				textScaleBox->SetStretch(EStretch::ScaleToFill);

				USizeBox* textSizeBox = NewObject<USizeBox>(this, USizeBox::StaticClass());
				textSizeBox->SetMinDesiredWidth(200.0f);
				textSizeBox->SetMinDesiredHeight(40.0f);
				textSizeBox->AddChild(textBlock);
				textScaleBox->AddChild(textSizeBox);

				ResultGameVerticalBox->AddChild(textScaleBox);
			}	
		}

		FScriptDelegate delegate;
		delegate.BindUFunction(this, FName("CloseWindow"));
		ResultGameVerticalBox->AddChild(CreateButton("Ok", delegate));

		Border->AddChild(ResultGameVerticalBox);
	}
}

void UETResultGameWidget::CloseWindow()
{
	if (UETGameInstance* gameInstance = Cast<UETGameInstance>(GetGameInstance()))
	{
		gameInstance->ClearGameRating();
		gameInstance->SetConnectToSession(false);
	}
	RemoveFromViewport();
}

UButton* UETResultGameWidget::CreateButton(FString NameOfButton, FScriptDelegate ClickDelegate)
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

	return button;
}
