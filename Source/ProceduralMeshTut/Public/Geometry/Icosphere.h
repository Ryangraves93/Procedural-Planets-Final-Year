// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <unordered_map>
#include "Containers/Map.h"
#include "ProceduralMeshComponent.h"
#include <vector>
#include "Icosphere.generated.h"

USTRUCT()
struct FTriangle
{
	GENERATED_BODY()

		// Use UPROPERTY() to decorate member variables as they allow for easier integration with network replication as well as potential garbage collection processing
		int vert[3];
};

USTRUCT()
struct Fuint32_pair_hash
{
	GENERATED_BODY()
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
		}hpair;
		hpair.A = x.first;
		hpair.B = x.second;
		
		size_t hash = 0;
		hash += x.second;
		hash = hash << 32;
		hash += x.first;
		check(hash == hpair.C);
		return hpair.C;
	}
};

namespace std
{
	template<typename K, typename V>
	using umap = std::unordered_map<K, V, Fuint32_pair_hash>;
}

UCLASS()
class AIcosphere : public AActor
{

	GENERATED_BODY()

public:	
	AIcosphere();
	void make_icosphere();

protected:
	virtual void BeginPlay() override;
	void Subdivide();
	uint32 FindMidPoint(uint32 v1, uint32 v2);
	void CalculateNormal(FTriangle& vert);

//Getters to retrieve planet attributes
public:	
	const TArray<FVector>& get_vertices() const { return m_vertices;  }
	const TArray<FTriangle>& get_triangles() const { return m_triangles; }
	const TArray<FVector>& get_normals() const { return m_normals; }
	uint32 get_index_count() const { return 3 * m_triangles.Num(); } //Multiply by three for each vertex
	const int* get_triangles_raw() const { return (int*)m_triangles.GetData(); }
	const float& get_radius() const { return Radius; }

	void IntializeValues(uint8 subdivisions, float radius);

	TArray<FLinearColor> PlanetColorValues;
	
	
private:

	int8 m_Subdivisions;

	UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProceduralMeshComponent* MeshComponent;

	UPROPERTY()
	UMaterialInstance* PlanetProjTex;

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	void construct_Icosphere();

	void Apply_Dynamic_Material();

	//Planet Attributes
	TArray<FVector> m_vertices;
	TArray<FVector> m_normals;
	TArray<FTriangle> m_triangles;
	TArray<int32> m_triangles32;

	float Radius;
	float X = .525731112119133606f;
	float Z = .850650808352039932f;
	const float N = 0.f;

	std::umap<std::pair<uint32, uint32>, uint32> lookup;

	// Vertices of the mesh formed from const vectors
	 TArray<FVector> Vertices =
	{
		{-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
		{N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
		{Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
	};

	//Index for the vertices to form each triangle
	const TArray<FTriangle> Triangles =
	{
		{0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
		{8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
		{7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
		{6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
	};

	float amplitude;

	UPROPERTY()
	class AIcosphere* unitsphere;

	UPROPERTY(EditAnywhere, Category = "Noise")
	float amplitudeMultiplier;

	UPROPERTY(EditAnywhere, Category = "Noise")
	float NoiseDivisional;

	UPROPERTY(EditAnywhere, Category = "ProcedrealMesh")
	bool generateMesh;

	virtual void OnConstruction(const FTransform& Transform) override;
};
