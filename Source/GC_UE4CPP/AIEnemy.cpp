// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy.h"
#include "Perception/PawnSensingComponent.h"
#include "AIEnemyController.h"
#include "GC_UE4CPPGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AAIEnemy::AAIEnemy()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SetPeripheralVisionAngle(90);
	IsPicking = false;
	FoodCounter = 0;
	SlowCarryMultiplier = 0.5;
}

// Called when the game starts or when spawned
void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AAIEnemy::OnCharacterSeen);
	}
	EnemyController = Cast<AAIEnemyController>(GetController());
}

// Called to bind functionality to input
void AAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIEnemy::OnCharacterSeen(APawn* Caught)
{
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

			EnemyController->GetBlackboardComp()->ClearValue("IsCarrying");

			GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed / SlowCarryMultiplier;

			PickedFood->SetPhysics(true);
		}
		else if (FoodCounter != 0)
		{
			IsPicking = true;
			IsCarrying = true;

			EnemyController->GetBlackboardComp()->SetValueAsBool("IsCarrying", true);

			GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * SlowCarryMultiplier;

			PickedFood = PickableFood.GetData()[0];
			PickedFood->SetPhysics(false);
		}
	}
}