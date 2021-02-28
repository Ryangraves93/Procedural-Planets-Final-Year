// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "SimpleTriangle.generated.h"

class UProceduralMeshComponent;

UCLASS()
class PROCEDURALMESHTUT_API ASimpleTriangle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleTriangle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProcedrealMesh")
	int32 height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProcedrealMesh")
	int32 width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProcedrealMesh")
	float spacing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProcedrealMesh")
	bool generateMesh;
	UProceduralMeshComponent* meshComponent;
	FVector mid;

	void GenerateVertices();
	void GenerateTriangles();
private:
	TArray<int32> index;
	TArray<FVector> Vertices;
	void ModifyVertices();
	
	void ClearMeshData();
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
