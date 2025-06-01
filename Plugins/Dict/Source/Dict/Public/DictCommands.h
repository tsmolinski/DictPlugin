// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DictStyle.h"

class FDictCommands : public TCommands<FDictCommands>
{
public:

	FDictCommands()
		: TCommands<FDictCommands>(TEXT("Dict"), NSLOCTEXT("Contexts", "Dict", "Dict Plugin"), NAME_None, FDictStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};