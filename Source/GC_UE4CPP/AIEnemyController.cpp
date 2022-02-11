#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

#include "AIEnemy.h"
#include "AIEnemyController.h"
#include "FoodSlot.h"

AAIEnemyController::AAIEnemyController()
{
	// Setup AI components
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
			{
				// Update the AI move target to where the AI seen the player for last time
				BlackboardComponent->SetValueAsVector("PreviousPosition", AIEnemy->GetActorLocation());
			}

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Saw you !"));

			// Update blackboard to set that the player has been seen
			BlackboardComponent->SetValueAsObject(PlayerKey, Caught);
			BlackboardComponent->SetValueAsBool("SeenPlayer", true);

			// Update the cooldown to check the ~~pur~~chase check
			GetWorld()->GetTimerManager().SetTimer(SeeTimerHandle, this, &AAIEnemyController::OnPurchase, 0.6, false);
																							//  --------
																							//	^ lol
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

		// Spawn the character and its AI

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFoodSlot::StaticClass(), PatrolPoints);
		Spawn = UGameplayStatics::GetActorOfClass(GetWorld(), AEnemiSpawn::StaticClass());


		BehaviorComponent->StartTree(*AIEnemy->BehaviorTree);
	}
}

void AAIEnemyController::OnPurchase() { BlackboardComponent->ClearValue("SeenPlayer"); }