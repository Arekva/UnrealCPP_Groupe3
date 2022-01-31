// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyController.h"
#include "AIEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PatrolPoint.h"

AAIEnemyController::AAIEnemyController()
{
	BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	DestinationKey = "Destination";
	PlayerKey = "Target";

	CurrentPatrolPoint = 0;
}

void AAIEnemyController::SetCharacterCaught(APawn* Caught)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsObject(PlayerKey, Caught);
	}
}

void AAIEnemyController::OnPossess(APawn* PawnPossessed)
{
	Super::OnPossess(PawnPossessed);

	AAIEnemy* AIEnemy = Cast<AAIEnemy>(PawnPossessed);

	if (AIEnemy)
	{
		if (AIEnemy->BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(AIEnemy->BehaviorTree->BlackboardAsset));
		}
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APatrolPoint::StaticClass(), PatrolPoints);

		BehaviorComponent->StartTree(*AIEnemy->BehaviorTree);
	}
}