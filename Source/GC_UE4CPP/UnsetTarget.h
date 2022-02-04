// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "BehaviorTree/BTTaskNode.h"
#include "UnsetTarget.generated.h"

/**
 *
 */
UCLASS()
class GC_UE4CPP_API UUnsetTarget : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
