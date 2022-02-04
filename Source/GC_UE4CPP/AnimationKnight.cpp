// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationKnight.h"
#include "MyCharacter.h"

UAnimationKnight::UAnimationKnight()
{
    IsWalking = false;
    IsCarrying = false;
    IsFinished = false;
    Won = false;
}

void UAnimationKnight::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Owner = TryGetPawnOwner();

    PlayerCharacter = Cast<AMyCharacter>(Owner);
}

void UAnimationKnight::NativeUpdateAnimation(float DeltaTimeX)
{
    Super::NativeUpdateAnimation(DeltaTimeX);

    if (!Owner)
    {
        return;
    }

    if (PlayerCharacter)
    {
        if (PlayerCharacter->GetVelocity().IsNearlyZero(0.5))
        {
            IsWalking = false;
        }
        else
        {
            IsWalking = true;
        }

        if (PlayerCharacter->IsCarrying)
        {
            IsCarrying = true;
        }
        else
        {
            IsCarrying = false;
        }

        if (PlayerCharacter->IsFinished)
        {
            IsFinished = true;
        }
        else
        {
            IsFinished = false;
        }

        if (PlayerCharacter->Won)
        {
            Won = true;
        }
        else
        {
            Won = false;
        }
    }
}

void UAnimationKnight::AnimNotify_Picking1(UAnimNotify* Notify)
{
    if (!PlayerCharacter->IsCarrying)
    {
        PlayerCharacter->IsPicking = false;
    }
}

void UAnimationKnight::AnimNotify_Picking2(UAnimNotify* Notify)
{
    if (PlayerCharacter->IsCarrying)
    {
        PlayerCharacter->IsPicking = false;
    }
}

void UAnimationKnight::AnimNotify_Grab(UAnimNotify* Notify)
{
    if (PlayerCharacter->IsCarrying)
    {
        PlayerCharacter->CarriedFood->AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Fist_RSocket"));
    }
    else
    {
        PlayerCharacter->CarriedFood->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    }
}