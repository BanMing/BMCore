// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BMCoreEditor : ModuleRules
{
    public BMCoreEditor(ReadOnlyTargetRules Target) : base(Target)
    {

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
            }
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "BMCore"
            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "BlueprintGraph",
                "Core",
                "CoreUObject",
                "DetailCustomizations",
                "Engine",
                "GraphEditor",
                "InputCore",
                "KismetCompiler",
                "PropertyEditor",
                "SharedSettingsWidgets",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "AssetTools",
                "DeveloperSettings",
                "EditorSubsystem",
                "ToolMenus",
                "ContentBrowser",
            }
            );

    }
}
