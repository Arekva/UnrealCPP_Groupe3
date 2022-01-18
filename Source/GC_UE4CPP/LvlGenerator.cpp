// Fill out your copyright notice in the Description page of Project Settings.


#include "LvlGenerator.h"
#include "Engine/World.h"


// Sets default values
ALvlGenerator::ALvlGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ALvlGenerator::BeginPlay()
{
	Super::BeginPlay();
    SpawnFloorTile();
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("BeginCalled"));
}

// Called every frame
void ALvlGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALvlGenerator::SpawnFloorTile()
{
    //If the usefulactorbp is valid
    if (FloorTileBP)
    {
        AFloorTile* TileRef = GetWorld()->SpawnActor<AFloorTile>(FloorTileBP, GetTransform());
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TileSpawned"));
    }

}