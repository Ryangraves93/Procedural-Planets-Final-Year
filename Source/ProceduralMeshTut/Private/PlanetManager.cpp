// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetManager.h"
#include "core.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Geometry/icosphere.h"



// Sets default values
APlanetManager::APlanetManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");
	if (MeshComponent) {
		MeshComponent->SetupAttachment(RootComponent);
		MeshComponent->SetWorldLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	numberOfPlanets = 3;
	
}

// Called when the game starts or when spawned
void APlanetManager::BeginPlay()
{
	Super::BeginPlay();
	GeneratePlanet();

}

void APlanetManager::GeneratePlanet()
{
	FVector RootPosition = FVector::ZeroVector;

	float DistanceFromCenter = 10000.f;

	uint8 planetsPerRing = 1;
	uint32 PlanetsToSpawn = 0;
	for (uint32 i = 0; i <= numberOfPlanets; ++i)
	{
		for (uint32 j = 0; j <= planetsPerRing; ++j)
		{
			float Tau = (UKismetMathLibrary::GetPI() * 2);
			float random = FMath::RandRange(0.f, 6.f);
			float angle = FMath::RandRange(0.f, Tau);

			float x = FMath::Cos(random) * DistanceFromCenter;
			float y = FMath::Sin(random) * DistanceFromCenter;

			FTransform SpawnLoc;
			FVector SpawnPosition = FVector(x * i, y * i, 0.f);
			SpawnLoc.SetLocation(SpawnPosition);

			AIcosphere* Planet = GetWorld()->SpawnActorDeferred<AIcosphere>(AIcosphere::StaticClass(), SpawnLoc); 
			Planet->IntializeValues(i, DistanceFromCenter, FMath::RandRange(0.f, 400.f), subdivisions);
			Planet->FinishSpawning(SpawnLoc);
			m_planets.Add(Planet);
		}
		planetsPerRing++;
	}
	
}




