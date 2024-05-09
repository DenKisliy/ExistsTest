// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ETFindSessionsWidget.h"
#include "GameFramework/PlayerState.h"

#include "ETMainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXISTSTEST_API UETMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* Border;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UETFindSessionsWidget> FindSessionsWidget;

private:
	FString SessionName;

	UETFindSessionsWidget* FindSessionResultWidget;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void CreateSession();

	UFUNCTION()
	void FindSessions();

private:
	void CreateButton(FString NameOfButton, FScriptDelegate ClickDelegate);

	FScriptDelegate CreateDelegate(UObject* Object, FString FunctionName);

};
