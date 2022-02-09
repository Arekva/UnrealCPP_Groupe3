// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEnemy.h"
#include "GameFramework/Actor.h"
#include "EnemiSpawn.generated.h"


UCLASS()
class GC_UE4CPP_API AEnemiSpawn : public AActor
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	AEnemiSpawn();
	
	UFUNCTION()
		void Spawn();

private:
	
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AAIEnemy> EnemyBP;
	
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFood> FoodBP;



	int SpawnedFoodCounter;

};
