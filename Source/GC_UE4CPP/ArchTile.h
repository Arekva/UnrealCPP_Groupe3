// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArchTile.generated.h"

UCLASS()
class GC_UE4CPP_API AArchTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArchTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* FloorStaticMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ArchStaticMesh;

	float ArchScale = 0.5f;
	float ArchY = -75;
	float ArchZ = 10;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
