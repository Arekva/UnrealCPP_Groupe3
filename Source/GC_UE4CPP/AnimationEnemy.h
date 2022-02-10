#pragma once

#include "CoreMinimal.h"

#include "AIEnemy.h"

#include "AnimationEnemy.generated.h"

class UAnimNotify;

UCLASS()
class GC_UE4CPP_API UAnimationEnemy : public UAnimInstance
{
	GENERATED_BODY()

public:
    UAnimationEnemy();

    virtual void NativeBeginPlay() override;

    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaTimeX) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        bool IsWalking;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        bool IsCarrying;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        bool IsPicking;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        bool IsFinished;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        bool Won;

    UPROPERTY()
        AAIEnemy* Enemy;

    UFUNCTION(BlueprintCallable, Category = "MyAnim")
        void AnimNotify_Picking1(UAnimNotify* Notify);

    UFUNCTION(BlueprintCallable, Category = "MyAnim")
        void AnimNotify_Picking2(UAnimNotify* Notify);

    UFUNCTION(BlueprintCallable, Category = "MyAnim")
        void AnimNotify_Grab(UAnimNotify* Notify);

    UFUNCTION()
        void EnemyVictory();

    UFUNCTION()
        void EnemyDefeat();

private:
    APawn* Owner;
};
