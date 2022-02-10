// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPointSelection.h"
#include "AIEnemyController.h"
#include "FoodSlot.h"
#include "EnemiSpawn.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UPatrolPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* EnemyController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (EnemyController)
	{
		UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();

		AFoodSlot* CurrentPoint = Cast<AFoodSlot>(BlackboardComponent->GetValueAsObject("Destination"));

		TArray<AActor*> AvailablePatrolPoints = EnemyController->GetPatrolPoints();

		AFoodSlot* NextPatrolPoint = nullptr;


		if (AvailablePatrolPoints.Num() == 10)
		{
			do
			{
				int index = FMath::RandRange(0, AvailablePatrolPoints.Num() - 1);
				NextPatrolPoint = Cast<AFoodSlot>(AvailablePatrolPoints[index]);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Index = %i"), index));
			} while (NextPatrolPoint->FoodPlaced && EnemyController->AIEnemy->IsCarrying);
		}


		BlackboardComponent->SetValueAsObject("Destination", NextPatrolPoint);
		BlackboardComponent->SetValueAsObject("Spawn", EnemyController->Spawn);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
