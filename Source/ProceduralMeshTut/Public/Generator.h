// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Generator.generated.h"

USTRUCT()
struct FTriangle
{
	GENERATED_BODY()
		// Use UPROPERTY() to decorate member variables as they allow for easier integration with network replication as well as potential garbage collection processing
	
	   int vert[3];
};


UCLASS()
class PROCEDURALMESHTUT_API AGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	const float Multiplier = 50.f;

	float X = .525731112119133606f * Multiplier;
	float Z = .850650808352039932f * Multiplier;
	const float N = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProceduralMeshComponent* CustomMesh;

	// Vertices of the mesh
	TArray<FVector> Vertices =
	{
		{-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
		{N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
		{Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
	};

	// Vertices of the triangle
	TArray<FTriangle> Triangles;

	//Creates a triangle that connects the given vertices
	void AddTriangle(int32 V1, int32 V2, int32 V3);

	void GenerateIcosahderon();

	void Subdivide();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
