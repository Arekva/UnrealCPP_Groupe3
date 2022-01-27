// Fill out your copyright notice in the Description page of Project Settings.


#include "WallTile.h"

// Sets default values
AWallTile::AWallTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;
	FloorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorStaticMesh"));
	WallStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallStaticMesh"));
	RootComponent = FloorStaticMesh;

	WallStaticMesh->SetupAttachment(FloorStaticMesh);
	WallStaticMesh->SetRelativeLocation(FVector(0, WallY, WallZ));
}

// Called when the game starts or when spawned
void AWallTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

