// Copyright Epic Games, Inc. All Rights Reserved.

#include "bvhGameMode.h"
#include "bvhCharacter.h"
#include "UObject/ConstructorHelpers.h"

AbvhGameMode::AbvhGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
