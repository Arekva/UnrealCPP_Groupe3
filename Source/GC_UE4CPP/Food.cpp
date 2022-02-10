// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Components/SphereComponent.h"
#include "MyCharacter.h"
#include "AIEnemy.h"

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

	SetPhysics(true);
	//this->SetPhysics(true);
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
	else
	{
		AAIEnemy* Enemy = Cast<AAIEnemy>(OtherActor);
		if (Enemy)
		{
			Enemy->PickableFood.Add(this);
			Enemy->FoodCounter++;
		}
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
	else
	{
		AAIEnemy* Enemy = Cast<AAIEnemy>(OtherActor);
		if (Enemy)
		{
			Enemy->PickableFood.Remove(this);
			Enemy->FoodCounter--;
		}
	}
}

void AFood::SetPhysics(bool State)
{
	auto collision_state = State ? ECollisionEnabled::PhysicsOnly : ECollisionEnabled::NoCollision;

	StaticMesh->SetCollisionEnabled(collision_state);
	StaticMesh->SetSimulatePhysics(State);

	//StaticMesh->SetSimulatePhysics(State);
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::FromInt(State));
}