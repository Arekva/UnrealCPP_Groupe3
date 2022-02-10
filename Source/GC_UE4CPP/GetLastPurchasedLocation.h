#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTTaskNode.h"
#include "GetLastPurchasedLocation.generated.h"

/**
 *
 */
UCLASS()
class GC_UE4CPP_API UGetLastPurchasedLocation : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
