// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGameWidget::SetProgress(float Percentage)
{
	this->FoodBar->SetPercent(Percentage);
}

void UGameWidget::SetProgress(UINT Current, UINT Max)
{
	this->FoodCountText->SetText(
		FText::FromString(FString::FromInt(Current) + TEXT("/") + FString::FromInt(Max)));

	if (Max != 0)
	{
		this->SetProgress((float)Current / (float)Max);
	}
	else
	{
		// On évite les NaN ou +Infinity
		this->SetProgress(0.0);
	}
}

void UGameWidget::SetWinFood(UINT amount)
{
	this->WinFood = amount;

	this->SetProgress(this->CurrentFood, amount);
}

void UGameWidget::SetCurrentFood(UINT amount)
{
	this->CurrentFood = amount;

	this->SetProgress(amount, this->WinFood);
}

