// Fill out your copyright notice in the Description page of Project Settings.


#include "Geometry/Icosphere.h"
#include "core.h"
#include "Containers/Array.h"
#include <array>

// Sets default values
Icosphere::Icosphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

//Resets the index buffers and calls subdivisions n number of times.
void Icosphere::make_icosphere(uint8 subdivisions)
{
	m_vertices.Reset(16);
	m_triangles.Reset(20);

	m_triangles.Append(icosahedron::Triangles);
	m_vertices.Append(icosahedron::Vertices);

	for (uint8 i = 0; i <= subdivisions; ++i)
	{
		subdivide();
	}

	for (Triangle& tri : m_triangles)
	{
		m_normals.Add(CalculateNormal(tri));
		//vert *= GenerateRadius(FMath::Atan2(vert.Y, vert.X),FMath::Acos(vert.Z/vert.Size())); //acos lat
	}
}

//For every triangle I subdivide each to create 4 triangles by using the midpoints of each as the new vertices. I create
//an array to store the new vertices. Once I finishing looping through each triangle I swap the old array with the new one.
void Icosphere::subdivide()
{
	TArray<Triangle> ArrayToSwap;
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
float Icosphere::GenerateRadius(float polar, float aziumuthal)
{
	return FMath::Sin(aziumuthal) + 1.f;
}

uint32 Icosphere::FindMidPoint(uint32 v1 , uint32 v2)
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
		point *= icosahedron::radius;
		m_vertices.Add(point);
	}

	return inserted.first->second;
}

FVector& Icosphere::CalculateNormal(Triangle& triangle)
{
	//Pass in the index number into the vertex array to retrieve 
	//the correct coordinate
	const FVector& v0 = m_vertices[triangle.vert[0]];
	const FVector& v1 = m_vertices[triangle.vert[1]];
	const FVector& v2 = m_vertices[triangle.vert[2]];

	triangle.face = (v1 - v0) + (v2 - v0);
	triangle.normal = FVector::CrossProduct(v1 - v0,v2 - v0);
	triangle.normal.Normalize();

	return triangle.normal;
}

