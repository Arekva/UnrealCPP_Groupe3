// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UDeathWidget::OnRestartClick()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	UGameplayStatics::OpenLevel(GetWorld(), "bapti");
}

void UDeathWidget::NativeConstruct()
{
	Super::NativeConstruct();


	RestartButton->OnClicked.AddDynamic(this, &UDeathWidget::OnRestartClick);
}