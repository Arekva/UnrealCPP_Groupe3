#include "GetLastPurchasedLocation.h"

#include "AIEnemyController.h"
#include "AIEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UGetLastPurchasedLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* EnemyController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());
	if (EnemyController)
	{
		EnemyController->GetBlackboardComp()->SetValueAsVector("LastPurchasedLocation", EnemyController->PlayerPawn->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
