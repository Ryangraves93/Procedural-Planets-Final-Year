// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <unordered_map>
#include "Containers/Map.h"
#include <vector>



struct Triangle
{
		// Use UPROPERTY() to decorate member variables as they allow for easier integration with network replication as well as potential garbage collection processing
		int vert[3];
		FVector normal = FVector::ZeroVector;
		FVector face  = FVector::ZeroVector;
};

namespace icosahedron
{
	const float radius = 200.f;
	const float X = .525731112119133606f * radius;
	const float Z = .850650808352039932f *radius;
	const float N = 0.f;

	// Vertices of the mesh formed from const vectors
	static const TArray<FVector> Vertices =
	{
		{-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
		{N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
		{Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
	};

	//Index for the vertices to form each triangle
	static const TArray<Triangle> Triangles =
	{
		{0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
		{8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
		{7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
		{6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
	};

}

struct uint32_pair_hash
{
	size_t operator()(const std::pair<uint32, uint32>& x) const
	{
		union
		{
			struct
			{
				uint32 A;
				uint32 B;
			};
			size_t C;
		}jeffrey;
		jeffrey.A = x.first;
		jeffrey.B = x.second;
		return jeffrey.C;
	}
};

namespace std
{
	template<typename K, typename V>
	using umap = std::unordered_map<K, V, uint32_pair_hash>;
}


class Icosphere 
{
public:	
	Icosphere();
	void make_icosphere(uint8);

protected:
	float GenerateRadius(float polar, float aziumuthal);
	void subdivide();
	uint32 FindMidPoint(uint32 v1, uint32 v2);
	FVector& CalculateNormal(Triangle& vert);

public:	
	const TArray<FVector>& get_vertices() const { return m_vertices;  }
	const TArray<Triangle>& get_triangles() const { return m_triangles; }
	const TArray<FVector>& get_normals() const { return m_normals; }
	uint32 get_index_count() const { return 3 * m_triangles.Num(); } //Multiply by three for each vertex

	const int* get_triangles_raw() const { return (int*)m_triangles.GetData(); }
private:
	TArray<FVector> m_vertices;
	TArray<FVector> m_normals;
	TArray<Triangle> m_triangles;
	std::umap<std::pair<uint32, uint32>, uint32> lookup;
	//std::umap<std::pair<uint32, uint32>, uint32> lookup;

};
