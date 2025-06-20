// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DictPlugin : ModuleRules
{
	public DictPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"});
		
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"});

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "DetailCustomizations", "PropertyEditor", "EditorStyle"});

			PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
		}
	}
}
