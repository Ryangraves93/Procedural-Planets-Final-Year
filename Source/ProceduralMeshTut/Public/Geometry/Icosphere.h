// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"



struct Triangle
{
		// Use UPROPERTY() to decorate member variables as they allow for easier integration with network replication as well as potential garbage collection processing

		int vert[3];
};

namespace icosahedron
{
	const float multiplier  = 5.f;
	const float X = .525731112119133606f * multiplier;
	const float Z = .850650808352039932f * multiplier;
	const float N = 0.f;

	// Vertices of the mesh
	static const TArray<FVector> Vertices =
	{
		{-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
		{N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
		{Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
	};

	static const TArray<Triangle> Triangles =
	{
		{0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
		{8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
		{7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
		{6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
	};

}

class Icosphere 
{
public:	
	// Sets default values for this actor's properties
	Icosphere();
	void make_icosphere();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	const TArray<FVector>& get_vertices() const { return m_vertices;  }
	const TArray<Triangle>& get_triangles() const { return m_triangles; }
	uint32 get_index_count() const { return 3 * m_triangles.Num(); } //Multiply by three for each vertex

	const int* get_triangles_raw() const { return (int*)m_triangles.GetData(); }

private:
	TArray<FVector> m_vertices;
	TArray<Triangle> m_triangles;

};
