// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyAI.h"
#include "AIEnemyController.h"
#include "EnemiSpawn.h"
#include "Kismet/GameplayStatics.h"
#include "GC_UE4CPPGameModeBase.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UDestroyAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* EnemyController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());
	AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());

	if (EnemyController)
	{
		APawn* EnemyPawn = EnemyController->GetPawn();
		EnemyPawn->Destroy();


	GameMode->DestroyAiDelegate.Broadcast();
		
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

