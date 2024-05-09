// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerElements/ETAttributeWidget.h"

void UETAttributeWidget::SetStartData()
{
	ProgressBar->SetPercent(1.0f);
	ProgressBar->SetFillColorAndOpacity(FLinearColor::Red);
}

void UETAttributeWidget::SetPercent(float Value)
{
	ProgressBar->SetPercent(Value);
}