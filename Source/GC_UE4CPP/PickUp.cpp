// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"

#include "AIEnemyController.h"
#include "AIEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UPickUp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* EnemyController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());
	if (EnemyController)
	{
		AAIEnemy* Enemy = EnemyController->AIEnemy;
		if (Enemy)
		{
			Enemy->PickUp();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Ennemy ok"));
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
