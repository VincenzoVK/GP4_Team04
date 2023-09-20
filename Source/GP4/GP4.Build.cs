// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GP4 : ModuleRules
{
	public GP4(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CEF3", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AIModule", "GameplayTasks", "NavigationSystem", "PhysicsCore", "MeshConversion" });
	}
}
