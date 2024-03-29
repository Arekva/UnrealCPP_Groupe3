// Fill out your copyright notice in the Description page of Project Settings.


#include "AMainMenu.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAMainMenu::AAMainMenu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAMainMenu::BeginPlay()
{
	Super::BeginPlay();

	UIInstance = CreateWidget(this, UIClass);

	UIInstance->AddToViewport();
	UIInstance->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}

