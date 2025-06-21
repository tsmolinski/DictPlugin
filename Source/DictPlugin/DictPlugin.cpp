// Copyright Epic Games, Inc. All Rights Reserved.

#include "DictPlugin.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDictPluginModule, DictPlugin, "DictPlugin" );

#if WITH_EDITOR

#include "Editor/PropertyEditor/Public/PropertyEditorModule.h"
#include "DictPlugin/DetailCustomization/DictCubeDetailCustomization.h"

#endif

void FDictPluginModule::StartupModule()
{
	UE_LOG( LogTemp, Warning, TEXT("FDictPluginModule::StartupModule"));

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	PropertyModule.RegisterCustomClassLayout("DictCube", FOnGetDetailCustomizationInstance::CreateStatic(&FDictCubeDetailCustomization::MakeInstance));
	
}

void FDictPluginModule::ShutdownModule()
{
	UE_LOG( LogTemp, Warning, TEXT("FDictPluginModule::ShutdownModule"));
}

bool FDictPluginModule::IsGameModule() const
{
	return true;
}