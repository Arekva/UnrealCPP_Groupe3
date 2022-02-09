// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiSpawn.h"
#include "GC_UE4CPPGameModeBase.h"

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

    Spawn();
	
}

// Called every frame
void AEnemiSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemiSpawn::Spawn()
{
    if (EnemyBP)
    {
        AAIEnemy* EnemyRef = GetWorld()->SpawnActor<AAIEnemy>(EnemyBP, GetTransform());
        if (FoodBP)
        {
            AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
            if (SpawnedFoodCounter - GameMode->FoodCounter < GameMode->Objective)
            {
                AFood* FoodRef = GetWorld()->SpawnActor<AFood>(FoodBP, GetTransform());
                FoodRef->SetPhysics(false);
                FoodRef->AttachToComponent(EnemyRef->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Fist_RSocket"));
                EnemyRef->IsCarrying = true;
                EnemyRef->PickableFood.Add(FoodRef);
            }
        }
    }
}
