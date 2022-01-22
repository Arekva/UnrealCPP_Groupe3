// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallTile.generated.h"

UCLASS()
class GC_UE4CPP_API AWallTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* FloorStaticMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* WallStaticMesh;

	float WallY = -90;
	float WallZ = 110;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
