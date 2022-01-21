// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyCharacter.h"
#include "AnimationKnight.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UAnimationKnight : public UAnimInstance
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        bool IsWalking;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        bool IsCarrying;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        bool IsFinished;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        bool Won;

    UPROPERTY()
    AMyCharacter* PlayerCharacter;

public:
    UAnimationKnight();

    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaTimeX) override;

    UFUNCTION(BlueprintCallable, Category = "MyAnim")
        void AnimNotify_Picking1(UAnimNotify* Notify);

    UFUNCTION(BlueprintCallable, Category = "MyAnim")
        void AnimNotify_Picking2(UAnimNotify* Notify);

private:
    APawn* Owner;

};
