// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GC_UE4CPPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AGC_UE4CPPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGC_UE4CPPGameModeBase();

	void Defeat();

	void Victory();

	int SetFood();

	int GetObjective();

private:
	int FoodCounter;

	UPROPERTY(EditAnywhere)
		int Objective;

};
