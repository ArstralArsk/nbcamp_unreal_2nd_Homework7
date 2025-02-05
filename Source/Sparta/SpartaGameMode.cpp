// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpartaGameMode::ASpartaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
