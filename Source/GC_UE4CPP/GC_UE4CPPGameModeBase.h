// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AnimationEnemy.h"
#include "GC_UE4CPPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AGC_UE4CPPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDefeatSignature);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVictorySignature);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDestroyAiSignature);




	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFoodPoseSignature, AFood*, Food);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFoodGrabSignature, AFood*, Food);
	
protected:
	virtual void BeginPlay() override;

public:
	AGC_UE4CPPGameModeBase();

	FDefeatSignature DefeatDelegate;

	FVictorySignature VictoryDelegate;

	FFoodPoseSignature FoodPoseDelegate;

	FFoodGrabSignature FoodGrabDelegate;

	FDestroyAiSignature DestroyAiDelegate;

	UFUNCTION()
	void Defeat();

	UFUNCTION()
	void Victory();

	int SetFood(AFood* Food);

	int GetObjective();

	int FoodCounter;

	UPROPERTY(EditAnywhere)
		int Objective;

};
