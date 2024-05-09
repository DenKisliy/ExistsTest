// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "../UI/MainMenu/ETMainMenuWidget.h"
#include "../UI/PlayerElements/ETAttributeWidget.h"
#include "../UI/PlayerElements/ETTimerWidget.h"
#include "../UI/MainMenu/ETResultGameWidget.h"

#include "ETGameInstance.h"

#include "ETHUD.generated.h"

/**
 * 
 */
UCLASS()
class EXISTSTEST_API AETHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Widget Static Class")
	TSubclassOf<UETMainMenuWidget> MainMenuStatic;

	UPROPERTY(EditAnywhere, Category = "Widget Static Class")
	TSubclassOf<UETTimerWidget> TimerStatic;

	UPROPERTY(EditAnywhere, Category = "Widget Static Class")
	TSubclassOf<UETAttributeWidget> AttributeStatic;

	UPROPERTY(EditAnywhere, Category = "Widget Static Class")
	TSubclassOf<UETResultGameWidget> ResultGameStatic;

private:
	UETTimerWidget* TimerWidget;

	UETAttributeWidget* AttributeWidget;

protected:
	virtual void BeginPlay() override;

public:
	void SetTimeForTimerWidget(int Time);

	void SetValueForAttribute(float Value);

};
