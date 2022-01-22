// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CornerTile.generated.h"

UCLASS()
class GC_UE4CPP_API ACornerTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACornerTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* FloorStaticMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* WallStaticMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* CornerWallStaticMesh;
	

	float WallY = -90;
	float WallZ = 110;
	float WallRotation = -90;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
