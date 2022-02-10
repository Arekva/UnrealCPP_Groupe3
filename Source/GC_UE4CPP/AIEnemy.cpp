#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

#include "AIEnemy.h"
#include "AIEnemyController.h"
#include "Food.h"

#include "GC_UE4CPPGameModeBase.h"

AAIEnemy::AAIEnemy()
{
	SlowCarryMultiplier = 0.5;
	EasyWalkSpeedMultiplicator = 0.75;

	FieldOfView = 90.0;
	CatchRange = 100.0;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SetPeripheralVisionAngle(FieldOfView);

	IsPicking = false;
	FoodCounter = 0;
}

void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComponent)
	{
		// Register the catch delegate
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AAIEnemy::OnCharacterSeen);
	}

	EnemyController = Cast<AAIEnemyController>(GetController());

	float WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	// if (game.easymode)
	// {
	//     WalkSpeed *= EasyWalkSpeedMultiplicator;
	// }
		
	MaxWalkSpeed = WalkSpeed; // cache the max walk speed
}

void AAIEnemy::OnCharacterSeen(APawn* Caught)
{
	if (EnemyController)
	{
		EnemyController->SetCharacterCaught(Caught);

		// Get if the player is close enough to the bad guy so he get caught and lose the game
		if (FVector::Distance(GetActorLocation(), Caught->GetActorLocation()) < CatchRange)
		{
			// Invoke the defeat delegate (defeat UI, animations, ...)
			Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode())->DefeatDelegate.Broadcast();
		}
	}
}

void AAIEnemy::PickUp()
{
	// Take/drop and do animations
	if (!IsPicking)
	{
		if (IsCarrying)
		{
			// Update food state machine:
			// 
			// drop the carried food on the floor and speed up the character again.

			IsPicking = true;
			IsCarrying = false;

			EnemyController->GetBlackboardComp()->ClearValue("IsCarrying");

			GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;

			PickedFood->SetPhysics(true); // enable food physics, can be kind of fun playing football with a Hamburger
		}
		else if (FoodCounter != 0)
		{
			// Update food state machine:
			// 
			// if there is a food to pick on the floor, do pick and carry it.
			// slow the character down.

			IsPicking = true;
			IsCarrying = true;

			EnemyController->GetBlackboardComp()->SetValueAsBool("IsCarrying", true);

			GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed * SlowCarryMultiplier;


			// Set the picked food handle to the first available food of the array.

			PickedFood = PickableFood.GetData()[0];
			PickedFood->SetPhysics(false); // disable physics to avoid character to be propulsed by food.
		}
	}
}