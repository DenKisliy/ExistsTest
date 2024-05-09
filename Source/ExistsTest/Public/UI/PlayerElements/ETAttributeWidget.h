// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"

#include "ETAttributeWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXISTSTEST_API UETAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ProgressBar;

public:
	void SetStartData();

	void SetPercent(float Value);
};
