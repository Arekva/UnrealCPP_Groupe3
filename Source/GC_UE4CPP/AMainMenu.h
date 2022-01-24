// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Blueprint/UserWidget.h"

#include "AMainMenu.generated.h"

UCLASS()
class GC_UE4CPP_API AAMainMenu : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMainMenu();

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> UI;

	UUserWidget* UIInstance;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
