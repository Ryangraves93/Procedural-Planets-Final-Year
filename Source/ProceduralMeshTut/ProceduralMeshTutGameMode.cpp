// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralMeshTutGameMode.h"
#include "ProceduralMeshTutCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProceduralMeshTutGameMode::AProceduralMeshTutGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		//DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
