// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy.h"
#include "Perception/PawnSensingComponent.h"
#include "AIEnemyController.h"
#include "GC_UE4CPPGameModeBase.h"

// Sets default values
AAIEnemy::AAIEnemy()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SetPeripheralVisionAngle(90);
	IsPicking = false;
}

// Called when the game starts or when spawned
void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AAIEnemy::OnCharacterSeen);
	}
}

// Called to bind functionality to input
void AAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIEnemy::OnCharacterSeen(APawn* Caught)
{
	AAIEnemyController* EnemyController = Cast<AAIEnemyController>(GetController());

	if (EnemyController)
	{
		EnemyController->SetCharacterCaught(Caught);
		if (FVector::Distance(GetActorLocation(), Caught->GetActorLocation()) < 100)
		{
			AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
			GameMode->DefeatDelegate.Broadcast();
		}
	}
}

void AAIEnemy::PickUp()
{
	if (!IsPicking)
	{
		if (IsCarrying)
		{
			IsPicking = true;
			IsCarrying = false;
		}
		else if (FoodCounter != 0)
		{
			IsPicking = true;
			IsCarrying = true;
		}
	}
}