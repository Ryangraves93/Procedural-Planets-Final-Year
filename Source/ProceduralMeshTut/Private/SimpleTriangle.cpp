// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleTriangle.h"
#include "core.h"
#include "DrawDebugHelpers.h"


// Sets default values
ASimpleTriangle::ASimpleTriangle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");
	meshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	if (meshComponent)
	{
		meshComponent->SetupAttachment(RootComponent);
		meshComponent->SetWorldLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	width = 4;
	height = 4;
	spacing = 50.0f;
	mid = FVector(spacing * width / 2, spacing * width / 2, 0.0f);
	generateMesh = false;

}

// Called when the game starts or when spawned
void ASimpleTriangle::BeginPlay()
{
	Super::BeginPlay();

	
}

void ASimpleTriangle::GenerateVertices()
{
	float uvSpacing = 1.0f / FMath::Max(height, width);

	for (int32 y = 0; y < height; y++)
	{
		for (int32 x = 0; x < width; x++)
		{
			Vertices.Add(FVector(x * spacing, y * spacing, 0.0f));
		}
	}
}

void ASimpleTriangle::GenerateTriangles()
{
	for (int32 y = 0; y < height - 1; y++)
	{
		for (int32 x = 0; x < width - 1; x++)
		{
			index.Add(x + (y * width));
			index.Add(x + (y * width) + width);
			index.Add(x + (y * width) + width + 1);

			index.Add(x + (y * width));
			index.Add(x + (y * width) + width + 1);
			index.Add(x + (y * width)  + 1);
		}
	}
	
}

void ASimpleTriangle::ModifyVertices()
{
	for (FVector& vert : Vertices)
	{
		if (vert.X == 100 && vert.Y == 100)
		{
			vert.Z = 64.0f;
		}
		else
		{
			vert.Z = 0.0f;
		}
	}
}


void ASimpleTriangle::ClearMeshData()
{
	Vertices.Empty();
	index.Empty();
}

void ASimpleTriangle::OnConstruction(const FTransform& Transform)
{
	if (generateMesh)
	{
		generateMesh = false;

		ClearMeshData();

		GenerateVertices();
		GenerateTriangles();
		mid = FVector((spacing * width) / 2, (spacing * width) / 2, 0.0f);
		TArray<FLinearColor> VertexColors;
		meshComponent->CreateMeshSection_LinearColor(0, Vertices, index, TArray<FVector>(), TArray<FVector2D>(), VertexColors, TArray<FProcMeshTangent>(), true);
	}
	
}

// Called every frame
void ASimpleTriangle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

