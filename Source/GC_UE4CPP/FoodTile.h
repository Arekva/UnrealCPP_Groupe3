// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoodTile.generated.h"

UCLASS()
class GC_UE4CPP_API AFoodTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* FloorStaticMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* TableStaticMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* PlateStaticMesh;

	float TableY = 10;
	float TableZ = 10;

	float PlateScale = 0.5f;
	float PlateY = -10;
	float PlateZ = 80;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
