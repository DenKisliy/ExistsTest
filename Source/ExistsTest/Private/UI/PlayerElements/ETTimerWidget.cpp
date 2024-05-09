// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerElements/ETTimerWidget.h"

void UETTimerWidget::SetTime(int Time)
{
	if (IsValid(TimeTextBlock))
	{
		FString timerText = "00:00";

		if (Time > 0)
		{
			int minutes = Time / 60;
			FString minutesText = minutes > 9 ? FString::FromInt(minutes) : "0" + FString::FromInt(minutes);

			int second = Time % 60;
			FString secondText = second > 9 ? FString::FromInt(second) : "0" + FString::FromInt(second);

			timerText = minutesText + ":" + secondText;
		}

		TimeTextBlock->SetVisibility(Time > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		TimeTextBlock->SetText(FText::FromString(timerText));
	}
}
