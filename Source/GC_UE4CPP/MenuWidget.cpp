// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UMenuWidget::OnStartClick()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	UGameplayStatics::OpenLevel(GetWorld(), "bapti");
}
void UMenuWidget::OnQuitClick()
{
	FGenericPlatformMisc::RequestExit(false);
}

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UMenuWidget::OnStartClick);
	QuitButton->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitClick);
}

