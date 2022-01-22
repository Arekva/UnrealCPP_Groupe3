// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.h"
#include "ArchTile.h"
#include "WallTile.h"
#include "CornerTile.h"

#include "LvlGenerator.generated.h"


UCLASS()
class GC_UE4CPP_API ALvlGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALvlGenerator();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFloorTile> FloorTileBP;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AWallTile> WallTileBP;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ACornerTile> CornerTileBP;
	UPROPERTY(EditDefaultsOnly)
		int LvlSizeX = 10;
	UPROPERTY(EditDefaultsOnly)
		int LvlSizeY = 10;
	UPROPERTY(VisibleAnywhere)
		float TileSize = 200;

	UFUNCTION()
		void SpawnFloorTile();
	UFUNCTION()
		void SpawnWallTile(float ZRotation);
	UFUNCTION()
		void GenerateLvl(int SizeX, int SizeY);
	UFUNCTION()
		void GenerateWalls(int SizeX, int SizeY);
	UFUNCTION()
		void SpawnCornerTile(float ZRotation);
};
