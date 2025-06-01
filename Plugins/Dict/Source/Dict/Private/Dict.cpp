// Copyright Epic Games, Inc. All Rights Reserved.

#include "Dict.h"
#include "DictStyle.h"
#include "DictCommands.h"
#include "LevelEditor.h"
#include "SDictionaryWidget.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName DictTabName("Dict");

#define LOCTEXT_NAMESPACE "FDictModule"

void FDictModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FDictStyle::Initialize();
	FDictStyle::ReloadTextures();

	FDictCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDictCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FDictModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDictModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DictTabName, FOnSpawnTab::CreateRaw(this, &FDictModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FDictTabTitle", "Dict"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FDictModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FDictStyle::Shutdown();

	FDictCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DictTabName);
}

TSharedRef<SDockTab> FDictModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FDictModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("Dict.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				//SNew(STextBlock)
				//.Text(WidgetText)
				SNew(SDictionaryWidget)
			]
		];
}

void FDictModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(DictTabName);
}

void FDictModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FDictCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDictCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDictModule, Dict)