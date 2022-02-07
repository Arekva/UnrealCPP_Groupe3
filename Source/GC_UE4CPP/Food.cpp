// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Components/SphereComponent.h"
#include "MyCharacter.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 100;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionCollider"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->InitSphereRadius(SphereRadius);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->SetStaticMesh(FoodMeshes[FMath::RandRange(0, FoodMeshes.Num() - 1)]);
	RootComponent = StaticMesh;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFood::Pickable);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AFood::Unpickable);
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFood::Pickable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* Actor = Cast<AMyCharacter>(OtherActor);
	if (Actor)
	{
		Actor->PickableFood.Add(this);
		Actor->FoodCounter++;
	}
}

void AFood::Unpickable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* Actor = Cast<AMyCharacter>(OtherActor);
	if (Actor)
	{
		Actor->PickableFood.Remove(this);
		Actor->FoodCounter--;
	}
}