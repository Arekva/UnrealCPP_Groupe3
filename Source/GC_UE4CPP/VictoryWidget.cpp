// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UVictoryWidget::OnRestartClick()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	UGameplayStatics::OpenLevel(GetWorld(), "LVLDesign");
}

void UVictoryWidget::NativeConstruct()
{
	Super::NativeConstruct();


	RestartButton->OnClicked.AddDynamic(this, &UVictoryWidget::OnRestartClick);
}