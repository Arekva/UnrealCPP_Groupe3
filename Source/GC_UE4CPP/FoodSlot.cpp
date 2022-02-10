// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodSlot.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "AIEnemy.h"
#include "GC_UE4CPPGameModeBase.h"

// Sets default values
AFoodSlot::AFoodSlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 100;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionCollider"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->InitSphereRadius(SphereRadius);
}

// Called when the game starts or when spawned
void AFoodSlot::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFoodSlot::CallBeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AFoodSlot::CallEndOverlap);
	
	AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->FoodPoseDelegate.AddDynamic(this, &AFoodSlot::FoodPose);
	GameMode->FoodGrabDelegate.AddDynamic(this, &AFoodSlot::FoodGrab);
}

// Called every frame
void AFoodSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFoodSlot::CallBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFood* Food = Cast<AFood>(OtherActor);
	
	if (Food != nullptr)
	{
		DepositableFood.Add(Food);
	}
}

void AFoodSlot::CallEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFood* Food = Cast<AFood>(OtherActor);

	if (Food != nullptr)
	{
		DepositableFood.Remove(Food);
	}
}

void AFoodSlot::FoodPose(AFood* Food)
{
	if (DepositableFood.Contains(Food) && FoodPlaced == nullptr)
	{
		Food->SetActorLocation(GetActorLocation());
		Food->SetActorRotation(GetActorRotation());
		FoodPlaced = Food;
		Food->SetPhysics(false);
	}
}

void AFoodSlot::FoodGrab(AFood* Food)
{
	if (Food == FoodPlaced)
	{
		FoodPlaced = nullptr;
	}
}