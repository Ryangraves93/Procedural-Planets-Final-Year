// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetManager.h"
#include "ProceduralMeshComponent.h"
#include "core.h"
#include "Geometry/icosphere.h"


Icosphere unitsphere;
// Sets default values
APlanetManager::APlanetManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");

	if (MeshComponent) {
		MeshComponent->SetupAttachment(RootComponent);
		MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	
}

// Called when the game starts or when spawned
void APlanetManager::BeginPlay()
{
	Super::BeginPlay();
	unitsphere.make_icosphere();
	construct_Icosphere();
}

// Called every frame
void APlanetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlanetManager::construct_Icosphere()
{
	
	m_triangles = TArray<int>(unitsphere.get_triangles_raw(), unitsphere.get_index_count());
	m_vertices = TArray<FVector>(unitsphere.get_vertices());
	static TArray<FColor> dummy_color;
	MeshComponent->CreateMeshSection(0, m_vertices, m_triangles, TArray<FVector>(), TArray<FVector2D>(), dummy_color, TArray<FProcMeshTangent>(), true);
}

