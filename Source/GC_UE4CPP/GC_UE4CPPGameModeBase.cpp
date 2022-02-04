// Copyright Epic Games, Inc. All Rights Reserved.


#include "GC_UE4CPPGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "AnimationKnight.h"
#include "Blueprint/UserWidget.h"
#include "AnimationEnemy.h"

AGC_UE4CPPGameModeBase::AGC_UE4CPPGameModeBase()
{
	FoodCounter = 0;
	Objective = 5;
}

void AGC_UE4CPPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	DefeatDelegate.AddDynamic(this, &AGC_UE4CPPGameModeBase::Defeat);
	VictoryDelegate.AddDynamic(this, &AGC_UE4CPPGameModeBase::Victory);
}

void AGC_UE4CPPGameModeBase::Defeat()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Cheh !"));
	AMyCharacter* Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Player->DisableInput(pc);

	Player->IsFinished = true;
	Player->Won = false;
	// Mort
	Player->DepthUI->SetVisibility(ESlateVisibility::Visible);
	pc->SetShowMouseCursor(true);
}

void AGC_UE4CPPGameModeBase::Victory()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Yay !"));
	AMyCharacter* Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Player->DisableInput(pc);

	Player->IsFinished = true;
	Player->Won = true;

	Player->VictoryUI->SetVisibility(ESlateVisibility::Visible);
	pc->SetShowMouseCursor(true);
}

void AGC_UE4CPPGameModeBase::SetFood()
{
	FoodCounter++;
	if (FoodCounter == Objective)
	{
		Victory();
	}
}
