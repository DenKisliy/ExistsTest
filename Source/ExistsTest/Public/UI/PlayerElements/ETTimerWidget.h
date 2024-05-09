// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"

#include "ETTimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXISTSTEST_API UETTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* Border;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TimeTextBlock;

public:
	void SetTime(int Time);
};
