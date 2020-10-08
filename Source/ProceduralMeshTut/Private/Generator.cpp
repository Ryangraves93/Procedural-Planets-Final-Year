// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Generator.h"

// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Custom Mesh");
	SetRootComponent(CustomMesh);
	CustomMesh->bUseAsyncCooking = true;

}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();
	GenerateIcosahderon();

}

void AGenerator::AddTriangle(int32 V1, int32 V2, int32 V3)
{
	Triangles.Add(V1);
	Triangles.Add(V2);
	Triangles.Add(V3);
}

void AGenerator::GenerateIcosahderon()
{

	//Reset vertices array
	//Reset triangles array

	Vertices.Add(FVector(-X, N, Z)); //lower left - 0
	Vertices.Add(FVector(X, N, Z)); //upper left - 1
	Vertices.Add(FVector(-X, N, -Z)); //lower right - 2 
	Vertices.Add(FVector(X, N, -Z)); //upper right - 3

	Vertices.Add(FVector(N, Z, X)); //lower left - 0
	Vertices.Add(FVector(N, Z, -X)); //upper left - 1
	Vertices.Add(FVector(N, -Z, X)); //lower right - 2 
	Vertices.Add(FVector(N, -Z, -X)); //upper right - 3

	Vertices.Add(FVector(Z, X, N)); //lower left - 0
	Vertices.Add(FVector(-Z, X, N)); //upper left - 1
	Vertices.Add(FVector(Z, -X, N)); //lower right - 2 
	Vertices.Add(FVector(-Z, -X, N)); //upper right - 3

	AddTriangle(0, 4, 1);
	AddTriangle(0, 9, 4);
	AddTriangle(9, 5, 4);
	AddTriangle(4, 5, 8);
	AddTriangle(4, 8, 1);

	AddTriangle(8, 10, 1);
	AddTriangle(8, 3, 10);
	AddTriangle(5, 3, 8);
	AddTriangle(5, 2, 3);
	AddTriangle(2, 7, 3);

	AddTriangle(7, 10, 3);
	AddTriangle(7, 6, 10);
	AddTriangle(7, 11, 6);
	AddTriangle(11, 0, 6);
	AddTriangle(0, 1, 6);

	AddTriangle(6, 1, 10);
	AddTriangle(9, 0, 11);
	AddTriangle(9, 11, 2);
	AddTriangle(9, 2, 5);
	AddTriangle(7, 2, 11);



	TArray<FLinearColor> VertexColors;
	VertexColors.Add(FLinearColor(0.f, 0.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(0.5f, 1.f, 0.5f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 1.f));

	CustomMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), VertexColors, TArray <FProcMeshTangent>(), true);
}

void AGenerator::Subdivide()
{


}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

