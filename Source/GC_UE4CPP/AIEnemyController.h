// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemiSpawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()

		UBehaviorTreeComponent* BehaviorComponent;

		UBlackboardComponent* BlackboardComponent;

		UPROPERTY(EditDefaultsOnly, Category = AI)
			FName DestinationKey;

		UPROPERTY(EditDefaultsOnly, Category = AI)
			FName PlayerKey;

		TArray<AActor*> PatrolPoints;
	public :
		AActor* Spawn;


		virtual void OnPossess(APawn* PawnPossessed) override;

public:
	AAIEnemyController();

	void SetCharacterCaught(APawn* Caught);

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComponent; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

	int32 CurrentPatrolPoint = 0;

};
