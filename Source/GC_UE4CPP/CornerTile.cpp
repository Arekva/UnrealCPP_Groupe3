// Fill out your copyright notice in the Description page of Project Settings.


#include "CornerTile.h"

// Sets default values
ACornerTile::ACornerTile()
{
	FRotator NewRotation = FRotator(0, WallRotation, 0);
	FQuat QuatRotation = FQuat(NewRotation);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FloorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorStaticMesh"));
	RootComponent = FloorStaticMesh;

	WallStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallStaticMesh"));
	WallStaticMesh->SetupAttachment(FloorStaticMesh);
	WallStaticMesh->SetRelativeLocation(FVector(0, WallY, WallZ));

	CornerWallStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CornerWallStaticMesh"));
	CornerWallStaticMesh->SetupAttachment(FloorStaticMesh);
	CornerWallStaticMesh->SetRelativeLocation(FVector(WallY, 0, WallZ));
	CornerWallStaticMesh->SetRelativeRotation(NewRotation);
}

// Called when the game starts or when spawned
void ACornerTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACornerTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

