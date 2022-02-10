#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "AIEnemy.generated.h"

class AFood;

UCLASS()
class GC_UE4CPP_API AAIEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AAIEnemy();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnCharacterSeen(APawn* Caught);

	UPROPERTY()
		class AAIEnemyController* EnemyController;

private:
	float FieldOfView;

	float MaxWalkSpeed;
	float EasyWalkSpeedMultiplicator;

public:
	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = AI)
		class UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(EditAnywhere)
		float SlowCarryMultiplier;

	UFUNCTION()
		void PickUp();

	bool IsCarrying, IsPicking;

	TArray<AFood*> PickableFood;
	int FoodCounter;

	AFood* PickedFood;

	float CatchRange;
};
