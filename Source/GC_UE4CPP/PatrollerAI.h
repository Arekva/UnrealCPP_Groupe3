// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"

#include "PatrollerAI.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API APatrollerAI : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		UBehaviorTree* Tree;
};
