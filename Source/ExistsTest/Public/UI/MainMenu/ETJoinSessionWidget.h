// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Components/ScaleBox.h"
#include "Blueprint/WidgetTree.h"

#include "../../Subsystem/ETSessionSubsystem.h"

#include "ETJoinSessionWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXISTSTEST_API UETJoinSessionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* Border;

private:
	FOnlineSessionSearchResult Session;

public:
	void CreateButton(FOnlineSessionSearchResult SessionInfo);

	UFUNCTION()
	void OnClickButton();
};
