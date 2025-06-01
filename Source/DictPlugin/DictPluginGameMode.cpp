// Copyright Epic Games, Inc. All Rights Reserved.

#include "DictPluginGameMode.h"
#include "DictPluginCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADictPluginGameMode::ADictPluginGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
