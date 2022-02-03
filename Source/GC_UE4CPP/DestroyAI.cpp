// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyAI.h"
#include "DestroyAI.h"
#include "AIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UDestroyAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* EnemyController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());
	if (EnemyController)
	{
		APawn* EnemyPawn = EnemyController->GetPawn();
		EnemyPawn->Destroy();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
