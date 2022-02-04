// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiSpawn.h"

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
    }
}
