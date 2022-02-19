#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "AnimationEnemy.h"
#include "AIEnemyController.h"
#include "GC_UE4CPPGameModeBase.h"
#include "Food.h"

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

    // End game delegate register
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
        IsWalking = !Enemy->GetVelocity().IsNearlyZero(0.5);
        IsCarrying = Enemy->IsCarrying;
        IsPicking = Enemy->IsPicking;
    }
}

void UAnimationEnemy::AnimNotify_Picking1(UAnimNotify* Notify)
{
    // Begin of grab animation
    if (!Enemy->IsCarrying)
    {
        Enemy->IsPicking = false;
    }
}

void UAnimationEnemy::AnimNotify_Picking2(UAnimNotify* Notify)
{
    // End of grab animation
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
            // Grab food for carrying

            Enemy->PickedFood->AttachToComponent(Enemy->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Fist_RSocket"));

            AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
            GameMode->FoodGrabDelegate.Broadcast(Enemy->PickedFood);
        }
        else if (Enemy->PickedFood)
        {
            // Drop food for carrying

            Enemy->PickedFood->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

            AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
            GameMode->FoodPoseDelegate.Broadcast(Enemy->PickedFood);
        }
    }
}

void UAnimationEnemy::EnemyVictory()
{
    // WIN !
    IsFinished = true;
    Won = true;

    Enemy->GetCharacterMovement()->StopActiveMovement();
    AAIEnemyController* EnemyController = Cast<AAIEnemyController>(Enemy->GetController());

    if (EnemyController)
    {
        EnemyController->GetBehaviorComp()->StopTree();
    }
}

void UAnimationEnemy::EnemyDefeat()
{
    // LOSE ! TAKE THE L
    IsFinished = true;
    Won = false;

    Enemy->GetCharacterMovement()->StopActiveMovement();
    AAIEnemyController* EnemyController = Cast<AAIEnemyController>(Enemy->GetController());

    if (EnemyController)
    {
        EnemyController->GetBehaviorComp()->StopTree();
    }
}