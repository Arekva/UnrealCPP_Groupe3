// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UINT WinFood;
	UINT CurrentFood;
public:
	void SetProgress(float Percentage);
	void SetProgress(UINT Current, UINT Max);

	void SetWinFood(UINT amount);
	void SetCurrentFood(UINT amount);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* FoodBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FoodCountText;
};
