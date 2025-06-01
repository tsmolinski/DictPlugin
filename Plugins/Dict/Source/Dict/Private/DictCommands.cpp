// Copyright Epic Games, Inc. All Rights Reserved.

#include "DictCommands.h"

#define LOCTEXT_NAMESPACE "FDictModule"

void FDictCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Dict", "Bring up Dict window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
