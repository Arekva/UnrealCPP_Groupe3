// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPointSelection.h"
#include "AIEnemyController.h"
#include "PatrolPoint.h"
#include "EnemiSpawn.h"
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


		NextPatrolPoint = Cast<APatrolPoint>(AvailablePatrolPoints[FMath::RandRange(0, 4)]);


		BlackboardComponent->SetValueAsObject("Destination", NextPatrolPoint);
		BlackboardComponent->SetValueAsObject("Spawn", EnemyController->Spawn);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
