// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Generator.generated.h"


//USTRUCT()
//struct FTriangle
//{
//	GENERATED_BODY()
//		// Use UPROPERTY() to decorate member variables as they allow for easier integration with network replication as well as potential garbage collection processing
//
//		int vert[3];
//};
//
//namespace icosahedron
//{
//	const float X = .525731112119133606f;
//	const float Z = .850650808352039932f;
//	const float N = 0.f;
//
//	// Vertices of the mesh
//	static const TArray<FVector> Vertices =
//	{
//		{-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
//		{N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
//		{Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
//	};
//
//	static const TArray<FTriangle> Triangles =
//	{
//		 {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
//		{8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
//		{7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
//		{6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
//	};
//
//}

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


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProceduralMeshComponent* CustomMesh;

	void GenerateIcosahderon();

	void Subdivide();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/*TArray<FVector> m_vertices;
	TArray<FTriangle> m_triangles;*/

};
