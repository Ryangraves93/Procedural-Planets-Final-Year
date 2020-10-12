// Fill out your copyright notice in the Description page of Project Settings.


#include "Geometry/Icosphere.h"
#include "Containers/Array.h"

// Sets default values
Icosphere::Icosphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

void Icosphere::make_icosphere()
{
	m_vertices.Reset(16);
	m_triangles.Reset(20);

	m_triangles.Append(icosahedron::Triangles);
	m_vertices.Append(icosahedron::Vertices);
}

//// Called when the game starts or when spawned
//void Icosphere::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void Icosphere::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
