// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodTile.h"

// Sets default values
AFoodTile::AFoodTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = FloorStaticMesh;
	FloorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorStaticMesh"));
	RootComponent = FloorStaticMesh;

	TableStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TableStaticMesh"));
	TableStaticMesh->SetupAttachment(FloorStaticMesh);

	TableStaticMesh->SetRelativeLocation(FVector(0, TableY, TableZ));

	PlateStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateStaticMesh"));
	PlateStaticMesh->SetupAttachment(TableStaticMesh);

	PlateStaticMesh->SetRelativeScale3D(FVector(PlateScale, PlateScale, PlateScale));
	PlateStaticMesh->SetRelativeLocation(FVector(0, PlateY, PlateZ));

}

// Called when the game starts or when spawned
void AFoodTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFoodTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

