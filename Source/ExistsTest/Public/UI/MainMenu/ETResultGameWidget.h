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

#include "../../GameFramework/ETGameInstance.h"
#include "GameFramework/PlayerState.h"

#include "ETResultGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXISTSTEST_API UETResultGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* Border;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* ResultGameVerticalBox;

public:
	void ShowResultOfGame();

	UFUNCTION()
	void CloseWindow();

private:
	UButton* CreateButton(FString NameOfButton, FScriptDelegate ClickDelegate);

};
