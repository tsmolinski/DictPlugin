// Copyright Epic Games, Inc. All Rights Reserved.

#include "DictPlugin.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDictPluginModule, DictPlugin, "DictPlugin" );

void FDictPluginModule::StartupModule()
{
	UE_LOG( LogTemp, Warning, TEXT("FDictPluginModule::StartupModule"));
}

void FDictPluginModule::ShutdownModule()
{
	UE_LOG( LogTemp, Warning, TEXT("FDictPluginModule::ShutdownModule"));
}

bool FDictPluginModule::IsGameModule() const
{
	return true;
}
