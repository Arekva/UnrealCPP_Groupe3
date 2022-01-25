// Fill out your copyright notice in the Description page of Project Settings.


#include "LvlGenerator.h"
#include "Engine/World.h"
#include "time.h"


// Sets default values
ALvlGenerator::ALvlGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ALvlGenerator::BeginPlay()
{
	Super::BeginPlay();
    GenerateLvl(LvlSizeX, LvlSizeY);
    GenerateWalls(LvlSizeX, LvlSizeY);
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("BeginCalled"));
    srand(time(NULL));
}

// Called every frame
void ALvlGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALvlGenerator::SpawnFloorTile()
{
    if (FloorTileBP)
    {
        AFloorTile* TileRef = GetWorld()->SpawnActor<AFloorTile>(FloorTileBP, GetTransform());
        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TileSpawned"));
    }
}

void ALvlGenerator::SpawnWallTile(float ZRotation)
{
    FVector NewLocation = GetActorLocation();
    FRotator NewRotation = FRotator(0, ZRotation, 0);
    FQuat QuatRotation = FQuat(NewRotation);

    if (WallTileBP)
    {
        AWallTile* TileRef = GetWorld()->SpawnActor<AWallTile>(WallTileBP, GetTransform());

        TileRef->AddActorLocalRotation(QuatRotation);
        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Rotation = %f"), ZRotation));
        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("WallTileSpawned"));
    }
}

void ALvlGenerator::SpawnCornerTile(float ZRotation)
{
    FVector NewLocation = GetActorLocation();
    FRotator NewRotation = FRotator(0, ZRotation, 0);
    FQuat QuatRotation = FQuat(NewRotation);

    if (CornerTileBP)
    {
        ACornerTile* TileRef = GetWorld()->SpawnActor<ACornerTile>(CornerTileBP, GetTransform());

        TileRef->AddActorLocalRotation(QuatRotation);
        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Rotation = %f"), ZRotation));
        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("WallTileSpawned"));
    }
}

void ALvlGenerator::SpawnFoodTile()
{
    if (FoodTileBP)
    {
        AFoodTile* TileRef = GetWorld()->SpawnActor<AFoodTile>(FoodTileBP, GetTransform());
        PlacedFoodTiles++;
        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TileSpawned"));
    }
}

void ALvlGenerator::GenerateLvl(int SizeX, int SizeY)
{
    int CoordX = SizeX;
    int CoordY = SizeY;
    int PrevY;
    int AvailableTiles = SizeX * SizeY;

    FVector SpawnPoint;
    FVector PrevSpawnPoint;
    FVector OriginSpawnPoint;


    SpawnPoint = GetActorLocation();
    OriginSpawnPoint = SpawnPoint;

    while (CoordX > 0)
    {
        PrevY = CoordY;
        PrevSpawnPoint = SpawnPoint;
        while (CoordY > 0)
        {
            SpawnPoint += FVector(TileSize, 0, 0);
            SetActorLocation(SpawnPoint);
            SpawnTile(AvailableTiles);
            AvailableTiles--;
            CoordY--;
        }
        CoordX--;
        CoordY = PrevY--;
        SpawnPoint = PrevSpawnPoint + FVector(0, TileSize, 0);
    }
    SetActorLocation(OriginSpawnPoint);
}

void ALvlGenerator::GenerateWalls(int SizeX, int SizeY)
{
    int CoordX = SizeX;
    int CoordY = SizeY;
   
    FVector SpawnPoint;
    FVector OriginSpawnPoint;
    SpawnPoint = GetActorLocation() + FVector(TileSize, 0, 0);

    while (CoordX > 1)
    {
        SpawnPoint += FVector(0, TileSize, 0);
        SetActorLocation(SpawnPoint);
        if (CoordX == 2)
            SpawnCornerTile(-90);
        else
            SpawnWallTile(-90);
        CoordX--;
        
    }
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("First Wall"));
    while (CoordY > 1)
    {
        SpawnPoint += FVector(TileSize, 0, 0);
        SetActorLocation(SpawnPoint);
        if (CoordY == 2)
            SpawnCornerTile(180);
        else
            SpawnWallTile(180);
        CoordY--;
    }
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Second Wall"));
    while (CoordX < SizeX)
    {
        SpawnPoint += FVector(0, -TileSize, 0);
        SetActorLocation(SpawnPoint);
        if (CoordX == SizeX - 1)
            SpawnCornerTile(90);
        else
            SpawnWallTile(90);
        CoordX++;
    }
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Third Wall"));
    while (CoordY < SizeY)
    {
        SpawnPoint += FVector(-TileSize, 0, 0);
        SetActorLocation(SpawnPoint);
        if (CoordY == SizeY - 1)
            SpawnCornerTile(0);
        else
            SpawnWallTile(0);
        CoordY++;
    }
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Fourth Wall"));
}

void ALvlGenerator::SpawnTile(int TileAvailable)
{
    int rng;

    if (TileAvailable == TotalFoodTiles - PlacedFoodTiles)
    {
        SpawnFoodTile();
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("just enough place"));
    }
    else if(PlacedFoodTiles < TotalFoodTiles)
    {
        rng = rand() % 2;
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Rand = %i"), rng));
        switch (rng)
        {
            case 0:
                SpawnFloorTile();
                break;
            case 1:
                SpawnFoodTile();
                break;
        }
    }
    else
    {
        SpawnFloorTile();
    }
}



