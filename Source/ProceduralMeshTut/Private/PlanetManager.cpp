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

//Checks if valid spawn point before spawning any icosphere.

bool APlanetManager::IsValidSpawnPoint(const FVector& SpawnPoint, const float& radius)
{
	bool isValid = true;
	for (const AIcosphere* planet : m_planets)
	{
		float distance = FVector::Distance(SpawnPoint, planet->GetActorLocation());

		if (distance < planet->get_radius() + radius)
		{
			isValid = false;
			break;
		}
	}

	return isValid;
}

//Randomly spawns the spheres on a ring based distribution. Incrementing
//how many spheres there are per ring as expanded. Currently a WIP.

void APlanetManager::GeneratePlanet()
{
	FVector RootPosition = FVector::ZeroVector;

	float DistanceFromCenter = 50000.f;

	uint8 planetsPerRing = 1;
	uint32 PlanetsToSpawn = 0;
	for (uint32 i = 1; i <= numberOfPlanets; ++i)
	{
		for (uint32 j = 1; j <= planetsPerRing; ++j)
		{
			float Tau = (UKismetMathLibrary::GetPI() * 2);
			float random = FMath::RandRange(0.f, 6.f);
			float angle = FMath::RandRange(0.f, Tau);

			float x = FMath::Cos(random) * DistanceFromCenter;
			float y = FMath::Sin(random) * DistanceFromCenter;
			float z = FMath::RandRange(-10000.f, 10000.f);

			FTransform SpawnLoc;
			FVector SpawnPosition = FVector((x * i) * 2.f, (y * i) * 2.f, z);

			bool bIsValidSpawn = false;
			float radius = FMath::RandRange(8000.f, 20000.f);

			while (!bIsValidSpawn)
			{
				random = FMath::RandRange(0.f, 6.f);
				angle = FMath::RandRange(0.f, Tau);

				x = FMath::Cos(random) * DistanceFromCenter;
				y = FMath::Sin(random) * DistanceFromCenter;
				SpawnPosition = FVector((x * i) * 2.f, (y * i) * 2.f, z);
				bIsValidSpawn = IsValidSpawnPoint(SpawnPosition, radius);
			}

		
			SpawnLoc.SetLocation(SpawnPosition);

			AIcosphere* Planet = GetWorld()->SpawnActorDeferred<AIcosphere>(AIcosphere::StaticClass(), SpawnLoc); 
			Planet->IntializeValues(subdivisions, radius);
			Planet->FinishSpawning(SpawnLoc);
			m_planets.Add(Planet);
		}
		planetsPerRing += planetMultiplier;
	}
	
}




