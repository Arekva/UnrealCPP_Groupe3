// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Components/SphereComponent.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionCollider"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->InitSphereRadius(40.0f);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

