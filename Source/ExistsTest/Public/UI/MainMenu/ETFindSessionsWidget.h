// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ETJoinSessionWidget.h"

#include "ETFindSessionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXISTSTEST_API UETFindSessionsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* Border;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UETJoinSessionWidget> JoinSessionWidget;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void CreateButtonForFindSession(bool bFindSession);

	void ShowInfoText(FString InfoText);
};
