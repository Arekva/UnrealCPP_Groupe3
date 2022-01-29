// Fill out your copyright notice in the Description page of Project Settings.


#include "DepositSlot.h"
#include "MyCharacter.h"

// Sets default values
ADepositSlot::ADepositSlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionCollider"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->InitBoxExtent(FVector(200, 200, 200));

}

// Called when the game starts or when spawned
void ADepositSlot::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADepositSlot::Depositable);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ADepositSlot::Undepositable);
}

// Called every frame
void ADepositSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADepositSlot::Depositable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("TEST !"));
	AMyCharacter* Actor = Cast<AMyCharacter>(OtherActor);
	if (Actor)
	{
		Actor->IsDepositable = true;
	}
}

void ADepositSlot::Undepositable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* Actor = Cast<AMyCharacter>(OtherActor);
	if (Actor)
	{
		Actor->IsDepositable = false;
	}
}