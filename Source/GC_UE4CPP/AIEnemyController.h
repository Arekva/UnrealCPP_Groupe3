#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BehaviorTreeComponent.h"

#include "AIController.h"
#include "EnemiSpawn.h"

#include "AIEnemyController.generated.h"

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

	virtual void OnPossess(APawn* PawnPossessed) override;

public:
	AAIEnemyController();

	void SetCharacterCaught(APawn* Caught);

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComponent; }
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComponent; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

	int32 CurrentPatrolPoint = 0;

	AActor* Spawn;
	APawn* PlayerPawn;
	AAIEnemy* AIEnemy;

private :
	FTimerHandle SeeTimerHandle;
	
	UFUNCTION()
		void OnPurchase();
};
