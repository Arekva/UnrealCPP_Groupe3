// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Food.h"
#include "MyCharacter.generated.h"

UCLASS()
class GC_UE4CPP_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		class UCameraComponent* CameraComp;

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void CameraZoom(float AxisValue);

	void PickUp();
	
	UPROPERTY(EditDefaultsOnly)
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere)
		float RotationSpeed;

	UPROPERTY(EditAnywhere)
		float SpringArmLength;

	UPROPERTY(EditAnywhere)
		float SpringArmHeight;

	UPROPERTY(EditAnywhere)
		float MinCameraZoom;

	UPROPERTY(EditAnywhere)
		float MaxCameraZoom;

	UPROPERTY(EditAnywhere)
		float ZoomSpeed;

	UPROPERTY(EditAnywhere)
		float SlowCarryMultiplier;

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<class UUserWidget> MainUIClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<class UUserWidget> DeathUIClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<class UUserWidget> VictoryUIClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	bool IsCarrying;

	bool IsPicking;

	bool IsFinished;

	bool Won;

	bool IsDepositable;

	TArray<AFood*> PickableFood;

	int FoodCounter;

	AFood* CarriedFood;



	class UUserWidget* MainUI;

	class UUserWidget* DepthUI;

	class UUserWidget* VictoryUI;
};
