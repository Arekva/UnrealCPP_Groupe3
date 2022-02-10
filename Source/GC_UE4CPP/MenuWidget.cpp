// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GC_UE4CPPGameModeBase.h"
#include "Components/Button.h"

void UMenuWidget::OnStartClick()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	UGameplayStatics::OpenLevel(GetWorld(), "LVLDesign");
}

void UMenuWidget::OnStartEzClick()
{
	AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		GameMode->EasyMode = true;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	UGameplayStatics::OpenLevel(GetWorld(), "LVLDesign");
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
	StartButtonEz->OnClicked.AddDynamic(this, &UMenuWidget::OnStartEzClick);
}

