// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlanetManager.generated.h"

DECLARE_STATS_GROUP(TEXT("Ryan"), STATGROUP_Test, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("Construct Mesh"), STAT_ConstructMesh,STATGROUP_Test);
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
	UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProceduralMeshComponent* MeshComponent;

	UFUNCTION(BlueprintCallable , Category = "Mesh")
	void construct_Icosphere();

	TArray<int> m_triangles;
	TArray<FVector> m_vertices;
	TArray<FVector> m_normals;
};
