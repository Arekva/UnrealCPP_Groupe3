// Fill out your copyright notice in the Description page of Project Settings.


#include "UnsetTarget.h"
#include "AIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UUnsetTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* EnemyController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());
	if (EnemyController)
	{
		//BlackBoardComponent->UnsetValue("Target");
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
