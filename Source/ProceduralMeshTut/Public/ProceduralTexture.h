// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralTexture.generated.h"

UCLASS()
class PROCEDURALMESHTUT_API AProceduralTexture : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralTexture();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void GenerateTexture();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
