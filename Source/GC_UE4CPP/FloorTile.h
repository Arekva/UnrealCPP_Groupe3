// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

UCLASS()
class GC_UE4CPP_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMesh;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
