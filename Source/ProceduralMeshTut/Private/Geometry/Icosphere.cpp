// Fill out your copyright notice in the Description page of Project Settings.


#include "Geometry/Icosphere.h"
#include "core.h"
#include "Containers/Array.h"
#include "Kismet/KismetMathLibrary.h"
#include <array>

// Sets default values
AIcosphere::AIcosphere()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh");

	if (MeshComponent)
	{
		MeshComponent->SetupAttachment(RootComponent);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> FoundMaterial(TEXT("/Game/Materials/Materials/M_PlanetSurface_Inst.M_PlanetSurface_Inst"));

	if (FoundMaterial.Succeeded())
	{
		PlanetProjTex = FoundMaterial.Object;
	}
	MeshComponent->SetMaterial(0, PlanetProjTex);

	NoiseDivisional = FMath::RandRange(.1f, .25f);

	generateMesh = false;
}

//Construct the triangles array. Adds a 3D Perlin Noise value to each vertex on the sphere.
//Then Creates a call to pass in the parameters to the create mesh component.

void AIcosphere::construct_Icosphere()
{
	m_triangles.Reserve(get_index_count());

	for (const FTriangle& tri : get_triangles())
	{
		for (uint8 i = 0; i < 3; ++i)
		{
			m_triangles32.Add(tri.vert[i]);
		}
	}

	for (FVector& vert : m_vertices)
	{
		vert += FMath::PerlinNoise3D(vert / (Radius * NoiseDivisional)) * amplitude * vert.GetSafeNormal();
	}

	static TArray<FColor> dummy_color;
	MeshComponent->CreateMeshSection(0, m_vertices, m_triangles32, m_normals, TArray<FVector2D>(), dummy_color, TArray<FProcMeshTangent>(), true);
}

void AIcosphere::BeginPlay()
{
	Super::BeginPlay();

	make_icosphere();
}

//Values set pre construction which add dynamic attributes to the
//spheres.
void AIcosphere::IntializeValues(uint8 subdivisions,float _radius)
{
	Radius = _radius;
	X *= Radius;
	Z *= Radius;

	m_Subdivisions = subdivisions;

	amplitudeMultiplier = FMath::RandRange(.050f, .15f);
	amplitude = Radius * amplitudeMultiplier;

	Apply_Dynamic_Material();

	TArray<FVector> ArrayToSwap =
	{
		{-X, N, Z}, { X,N,Z }, { -X,N,-Z }, { X,N,-Z },
		{ N,Z,X }, { N,Z,-X }, { N,-Z,X }, { N,-Z,-X },
		{ Z,X,N }, { -Z,X, N }, { Z,-X,N }, { -Z,-X, N }
	};

	Swap(Vertices, ArrayToSwap);
}

//Resets the index buffers and calls subdivisions n number of times.
void AIcosphere::make_icosphere()
{
	m_vertices.Reset(20);
	m_triangles.Reset(20);

	m_vertices.Append(Vertices);
	m_triangles.Append(Triangles);


	for (FVector& vert : m_vertices)
	{
		m_normals.Add(vert);
	}

	for (uint8 i = 0; i <= m_Subdivisions; ++i)
	{
		Subdivide();
	}

	construct_Icosphere();
}

//For every triangle subdivide each to create 4 triangles by using the midpoints of each as the new vertices. I create
//an array to store the new vertices. Once finishing looping through each triangle swap the old array with the new one.
void AIcosphere::Subdivide()
{
	TArray<FTriangle> ArrayToSwap;
	ArrayToSwap.Reserve(m_triangles.Num() * 3);

	for (auto& triangle : m_triangles)
	{
		std::array<int, 3> mid;
		for (int edge = 0; edge < 3; ++edge)
		{
			mid[edge] = FindMidPoint(triangle.vert[edge], triangle.vert[(edge + 1) % 3]);
		}

		ArrayToSwap.Add({ triangle.vert[0], mid[0] , mid[2] });
		ArrayToSwap.Add({ triangle.vert[1], mid[1] , mid[0] });
		ArrayToSwap.Add({ triangle.vert[2], mid[2] , mid[1] });
		ArrayToSwap.Add({ mid[0], mid[1] , mid[2] });
	}

	Swap(m_triangles, ArrayToSwap);

	lookup.clear();
}


uint32 AIcosphere::FindMidPoint(uint32 v1, uint32 v2)
{
	uint32 a = std::min(v1, v2);
	uint32 b = std::max(v1, v2);
	std::pair<uint32, uint32> key(a, b);

	auto inserted = lookup.insert({ key, m_vertices.Num() });

	if (inserted.second)
	{
		FVector& edge0 = m_vertices[a];
		FVector& edge1 = m_vertices[b];

		FVector point = edge0 + edge1;

		point.Normalize();

		m_normals.Add(point);

		point *= Radius;

		m_vertices.Add(point);
	}

	return inserted.first->second;
}


//
void AIcosphere::CalculateNormal(FTriangle& triangle)
{
	//Pass in the index number into the vertex array to retrieve 
	//the correct coordinate
	const FVector& v0 = m_vertices[triangle.vert[0]];

	const FVector& v1 = m_vertices[triangle.vert[1]];

	const FVector& v2 = m_vertices[triangle.vert[2]];
}


void AIcosphere::Apply_Dynamic_Material()
{

	UMaterialInstanceDynamic* MaterialReference = MeshComponent->CreateDynamicMaterialInstance(0);


	if (MaterialReference)
	{
		MeshComponent->SetMaterial(0, MaterialReference);
		MaterialReference->SetScalarParameterValue(FName("PlanetRadius"), Radius);
		MaterialReference->SetScalarParameterValue(FName("MaxPlanetRadius"), Radius + amplitude);
		MaterialReference->SetScalarParameterValue(FName("MinPlanetRadius"), Radius - amplitude);
		FLinearColor color = FLinearColor(0.6f, 0.6f, 0.2f, 1.0f);

		FLinearColor MountainColor = FLinearColor(FMath::RandRange(0.5f, 1.f), FMath::RandRange(0.5f, 1.f), FMath::RandRange(0.5f, 1.f));
		FLinearColor SeaLevel = FLinearColor(FMath::RandRange(0.01f, 0.2f), FMath::RandRange(0.01f, 0.2f), FMath::RandRange(0.4f, 1.f));
		FLinearColor Terrain = FLinearColor(FMath::RandRange(0.01f, 0.5f), FMath::RandRange(0.01f, 0.5f), FMath::RandRange(0.01f, 0.5f));

		MaterialReference->SetVectorParameterValue(FName("Terrain"), Terrain);
		MaterialReference->SetVectorParameterValue(FName("MountainLevel"), MountainColor);
		MaterialReference->SetVectorParameterValue(FName("SeaLevel"), SeaLevel);
	}
}

void AIcosphere::OnConstruction(const FTransform& Transform)
{
	if (generateMesh)
	{
		generateMesh = false;

		make_icosphere();

		Apply_Dynamic_Material();
	}
}


