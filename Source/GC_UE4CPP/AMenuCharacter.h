// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMenuCharacter.generated.h"

UCLASS()
class GC_UE4CPP_API AAMenuCharacter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAMenuCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
