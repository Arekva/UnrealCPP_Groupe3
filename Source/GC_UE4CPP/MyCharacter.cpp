// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
// UI
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "DeathWidget.h"
#include "VictoryWidget.h"
//
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DepositSlot.h"
#include "GC_UE4CPPGameModeBase.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	RotationSpeed = 540;
	SpringArmLength = 300;
	SpringArmHeight = 170;
	MinCameraZoom = 50;
	MaxCameraZoom = 500;
	ZoomSpeed = 100;
	IsPicking = false;
	IsFinished = false;
	Won = false;
	IsDepositable = false;

	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, RotationSpeed, 0.0f);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

	SpringArmComp->SetupAttachment(GetMesh());

	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->TargetArmLength = SpringArmLength;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, SpringArmHeight));

	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/* UI de mort - Arthur */

	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	DepthUI = CreateWidget(pc, DeathUIClass);
	DepthUI->AddToViewport();
	DepthUI->SetVisibility(ESlateVisibility::Hidden);

	VictoryUI = CreateWidget(pc, VictoryUIClass);
	VictoryUI->AddToViewport();
	VictoryUI->SetVisibility(ESlateVisibility::Hidden);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("CameraZoom", this, &AMyCharacter::CameraZoom);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AMyCharacter::PickUp);
}

void AMyCharacter::MoveForward(float AxisValue)
{
	if ((Controller != nullptr) && (AxisValue != 0.0f) && !IsPicking)
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
}

void AMyCharacter::MoveRight(float AxisValue)
{
	if ((Controller != nullptr) && (AxisValue != 0.0f) && !IsPicking)
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// Add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
}

void AMyCharacter::CameraZoom(float AxisValue)
{
	if ((SpringArmComp->TargetArmLength >= MinCameraZoom && SpringArmComp->TargetArmLength <= MaxCameraZoom) || (SpringArmComp->TargetArmLength <= MinCameraZoom && AxisValue > 0) || (SpringArmComp->TargetArmLength >= MaxCameraZoom && AxisValue < 0))
	{
		SpringArmComp->TargetArmLength += AxisValue * ZoomSpeed;
	}
}

void AMyCharacter::PickUp()
{
	if (!IsPicking)
	{
		if (IsCarrying)
		{
			IsPicking = true;
			IsCarrying = false;
			if (IsDepositable)
			{
				AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
				GameMode->SetFood();
			}
		}
		else if (FoodCounter != 0)
		{
			IsPicking = true;
			IsCarrying = true;
		}
	}
}