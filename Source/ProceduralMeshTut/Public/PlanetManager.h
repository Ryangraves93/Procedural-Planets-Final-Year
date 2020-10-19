// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlanetManager.generated.h"

class UProceduralMeshComponent;

UCLASS()
class PROCEDURALMESHTUT_API APlanetManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanetManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh");
	uint8 subdivisions;

private:
	UPROPERTY(Category = PPawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UProceduralMeshComponent* MeshComponent;

	void construct_Icosphere();
	TArray<int> m_triangles;
	TArray<FVector> m_vertices;
};
