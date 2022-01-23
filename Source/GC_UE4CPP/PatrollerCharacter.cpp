// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrollerCharacter.h"
#include "PatrollerAI.h"

#include "BehaviorTree/BlackboardData.h"

#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
APatrollerCharacter::APatrollerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//this->AIControllerClass = CreateDefaultSubobject<APatrollerAI>(TEXT("AI"));
	//this->AIControllerClass = APatrollerAI;
	//this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//this->Collider
}

// Called when the game starts or when spawned
void APatrollerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APatrollerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APatrollerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

