// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiSpawn.h"
#include "GC_UE4CPPGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AEnemiSpawn::AEnemiSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemiSpawn::BeginPlay()
{
	Super::BeginPlay();
    AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
    GameMode->DestroyAiDelegate.AddDynamic(this, &AEnemiSpawn::DelaySpawn);
    Spawn();
    GetWorld()->GetTimerManager().SetTimer(SecondEnemyDelay, this, &AEnemiSpawn::Spawn, 1, false);
    GetWorld()->GetTimerManager().SetTimer(ThirdEnemyDelay, this, &AEnemiSpawn::Spawn, 10, false);
}

// Called every frame
void AEnemiSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemiSpawn::DelaySpawn()
{
    float time = FMath::RandRange(0.1f, 5.0f);
    FTimerHandle handle;
    GetWorld()->GetTimerManager().SetTimer(handle, this, &AEnemiSpawn::Spawn, time, false);
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("DelaySpawn")));
}

void AEnemiSpawn::Spawn()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Spawn")));
    if (EnemyBP)
    {
        AAIEnemy* EnemyRef = GetWorld()->SpawnActor<AAIEnemy>(EnemyBP, GetTransform());
        if (FoodBP)
        {
            AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
            if (SpawnedFoodCounter - GameMode->FoodCounter < GameMode->Objective)
            {
                SpawnedFoodCounter++;

                AFood* FoodRef = GetWorld()->SpawnActor<AFood>(FoodBP, GetTransform());
                FoodRef->SetPhysics(false);
                FoodRef->AttachToComponent(EnemyRef->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Fist_RSocket"));
                EnemyRef->IsCarrying = true;

                AAIEnemyController* EnemyController = Cast<AAIEnemyController>(EnemyRef->GetController());
                EnemyController->GetBlackboardComp()->SetValueAsBool("IsCarrying", true);

                EnemyRef->PickableFood.Add(FoodRef);
                EnemyRef->PickedFood = EnemyRef->PickableFood[0];

                EnemyRef->FoodCounter++;
                EnemyRef->GetCharacterMovement()->MaxWalkSpeed = EnemyRef->GetCharacterMovement()->MaxWalkSpeed * EnemyRef->SlowCarryMultiplier;

            }
        }
    }
}

