// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationEnemy.h"

UAnimationEnemy::UAnimationEnemy()
{
    IsWalking = false;
    IsCarrying = false;
    IsFinished = false;
    Won = false;
}

void UAnimationEnemy::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Owner = TryGetPawnOwner();

    Enemy = Cast<AAIEnemy>(Owner);
}

void UAnimationEnemy::NativeUpdateAnimation(float DeltaTimeX)
{
    Super::NativeUpdateAnimation(DeltaTimeX);

    if (!Owner)
    {
        return;
    }

    if (Enemy)
    {
        if (Enemy->GetVelocity().IsNearlyZero(0.5))
        {
            IsWalking = false;
        }
        else
        {
            IsWalking = true;
        }

        if (Enemy->IsCarrying)
        {
            IsCarrying = true;
        }
        else
        {
            IsCarrying = false;
        }
    }
}

void UAnimationEnemy::AnimNotify_Picking1(UAnimNotify* Notify)
{
    if (!Enemy->IsCarrying)
    {
        Enemy->IsPicking = false;
    }
}

void UAnimationEnemy::AnimNotify_Picking2(UAnimNotify* Notify)
{
    if (Enemy->IsCarrying)
    {
        Enemy->IsPicking = false;
    }
}

void UAnimationEnemy::AnimNotify_Grab(UAnimNotify* Notify)
{
    if (Enemy->IsCarrying)
    {
        Enemy->PickableFood[0]->AttachToComponent(Enemy->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Fist_RSocket"));
    }
    else
    {
        Enemy->PickableFood[0]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    }
}