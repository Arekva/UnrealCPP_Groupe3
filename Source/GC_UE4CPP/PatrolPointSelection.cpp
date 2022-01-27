// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPointSelection.h"
#include "AIEnemyController.h"
#include "PatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UPatrolPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* EnemyController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (EnemyController)
	{
		UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();

		APatrolPoint* CurrentPoint = Cast<APatrolPoint>(BlackboardComponent->GetValueAsObject("Destination"));

		TArray<AActor*> AvailablePatrolPoints = EnemyController->GetPatrolPoints();

		APatrolPoint* NextPatrolPoint = nullptr;

		if (EnemyController->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
		{
			NextPatrolPoint = Cast<APatrolPoint>(AvailablePatrolPoints[++EnemyController->CurrentPatrolPoint]);
		}
		else
		{
			NextPatrolPoint = Cast<APatrolPoint>(AvailablePatrolPoints[0]);
			EnemyController->CurrentPatrolPoint = 0;
		}

		BlackboardComponent->SetValueAsObject("Destination", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
