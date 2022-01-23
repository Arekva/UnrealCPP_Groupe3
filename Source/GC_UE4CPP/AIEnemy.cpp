// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy.h"
#include "Perception/PawnSensingComponent.h"
#include "AIEnemyController.h"

// Sets default values
AAIEnemy::AAIEnemy()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SetPeripheralVisionAngle(90);
}

// Called when the game starts or when spawned
void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AAIEnemy::OnCharacterCaught);
	}
}

// Called to bind functionality to input
void AAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIEnemy::OnCharacterCaught(APawn* Caught)
{
	AAIEnemyController* EnemyController = Cast<AAIEnemyController>(GetController());

	if (EnemyController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Cheh !"));
		EnemyController->SetCharacterCaught(Caught);
	}
}