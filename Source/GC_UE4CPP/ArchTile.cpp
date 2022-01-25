// Fill out your copyright notice in the Description page of Project Settings.


#include "ArchTile.h"

// Sets default values
AArchTile::AArchTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FloorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorStaticMesh"));
	ArchStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArchStaticMesh"));
	RootComponent = FloorStaticMesh;

	ArchStaticMesh->SetupAttachment(FloorStaticMesh);
	ArchStaticMesh->SetRelativeScale3D(FVector(ArchScale, ArchScale, ArchScale));
	ArchStaticMesh->SetRelativeLocation(FVector(0, ArchY, ArchZ));
}

// Called when the game starts or when spawned
void AArchTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArchTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

