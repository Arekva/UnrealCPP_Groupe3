// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyController.h"
#include "AIEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FoodSlot.h"

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
		if (Caught == PlayerPawn)
		{
			if (!BlackboardComponent->GetValueAsBool("SeenPlayer"))
				BlackboardComponent->SetValueAsVector("PreviousPosition", AIEnemy->GetActorLocation());

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Saw you !"));
			BlackboardComponent->SetValueAsObject(PlayerKey, Caught);
			BlackboardComponent->SetValueAsBool("SeenPlayer", true);
			GetWorld()->GetTimerManager().SetTimer(SeeTimerHandle, this, &AAIEnemyController::OnPurchase, 0.6, false);
		}
	}
}

void AAIEnemyController::OnPossess(APawn* PawnPossessed)
{
	Super::OnPossess(PawnPossessed);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	AIEnemy = Cast<AAIEnemy>(PawnPossessed);

	if (AIEnemy)
	{
		if (AIEnemy->BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(AIEnemy->BehaviorTree->BlackboardAsset));
		}
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFoodSlot::StaticClass(), PatrolPoints);
		Spawn = UGameplayStatics::GetActorOfClass(GetWorld(), AEnemiSpawn::StaticClass());


		BehaviorComponent->StartTree(*AIEnemy->BehaviorTree);
	}
}

void AAIEnemyController::OnPurchase()
{
	BlackboardComponent->ClearValue("SeenPlayer");
}