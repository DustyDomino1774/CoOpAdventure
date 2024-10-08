// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoOpAdventureGameMode.h"
#include "CoOpAdventureCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACoOpAdventureGameMode::ACoOpAdventureGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
