// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationEnemy.h"
#include "GC_UE4CPPGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIEnemyController.h"

UAnimationEnemy::UAnimationEnemy()
{
    IsWalking = false;
    IsCarrying = false;
    IsFinished = false;
    Won = false;
}

void UAnimationEnemy::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());

    GameMode->DefeatDelegate.AddDynamic(this, &UAnimationEnemy::EnemyVictory);
    GameMode->VictoryDelegate.AddDynamic(this, &UAnimationEnemy::EnemyDefeat);
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

        if (Enemy->IsPicking)
        {
            IsPicking = true;
        }
        else
        {
            IsPicking = false;
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
    if (Enemy)
    {
        if (Enemy->IsCarrying)
        {
            Enemy->PickedFood->AttachToComponent(Enemy->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Fist_RSocket"));
            AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
            GameMode->FoodGrabDelegate.Broadcast(Enemy->PickedFood);
        }
        else
        {
            if (Enemy->PickedFood)
            {
                Enemy->PickedFood->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

                AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
                GameMode->FoodPoseDelegate.Broadcast(Enemy->PickedFood);
            }
        }
    }
}

void UAnimationEnemy::EnemyVictory()
{
    IsFinished = true;
    Won = true;
    UCharacterMovementComponent* Movement = Enemy->GetCharacterMovement();
    Movement->StopActiveMovement();
    AAIEnemyController* EnemyController = Cast<AAIEnemyController>(Enemy->GetController());
    if (EnemyController)
    {
        EnemyController->GetBehaviorComp()->StopTree();
    }
}

void UAnimationEnemy::EnemyDefeat()
{
    IsFinished = true;
    Won = false;
    UCharacterMovementComponent* Movement = Enemy->GetCharacterMovement();
    Movement->StopActiveMovement();
    AAIEnemyController* EnemyController = Cast<AAIEnemyController>(Enemy->GetController());
    if (EnemyController)
    {
        EnemyController->GetBehaviorComp()->StopTree();
    }
}