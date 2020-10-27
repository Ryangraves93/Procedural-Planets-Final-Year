// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetManager.h"
#include "ProceduralMeshComponent.h"
#include "core.h"
#include "DrawDebugHelpers.h"
#include "Geometry/icosphere.h"


Icosphere unitsphere;
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

	subdivisions = 4;
}

// Called when the game starts or when spawned
void APlanetManager::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(0.0f, 0.0f, 0.0f));

	unitsphere.make_icosphere(subdivisions);
	construct_Icosphere();
}

//Fill the triangles and vertices from the instance of icosphere.
void APlanetManager::construct_Icosphere()
{
	m_triangles.Reserve(unitsphere.get_index_count());

	for (const Triangle& tri : unitsphere.get_triangles())
	{
		for (uint8 i = 0; i < 3; ++i)
		{
			m_triangles.Add(tri.vert[i]);
		}

		DrawDebugDirectionalArrow(GetWorld(),tri.face, (tri.normal * icosahedron::radius) *1.05, 20.f,FColor::Red, true);
	}
	static TArray<FColor> dummy_color;
	MeshComponent->CreateMeshSection(0, unitsphere.get_vertices(), m_triangles, unitsphere.get_normals(), TArray<FVector2D>(), dummy_color, TArray<FProcMeshTangent>(), true);
}

