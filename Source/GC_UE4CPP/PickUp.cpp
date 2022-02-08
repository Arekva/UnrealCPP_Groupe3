// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"

#include "AIEnemyController.h"
#include "AIEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UPickUp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/*AAIEnemyController* EnemyController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());
	if (EnemyController)
	{

	}*/
	AAIEnemy* Enemy = Cast<AAIEnemy>(OwnerComp.GetAIOwner());
	if (Enemy)
	{
		Enemy->PickUp();
	}
	return EBTNodeResult::Failed;
}
