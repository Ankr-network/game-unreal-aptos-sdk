// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.Collections.Generic;
using System.IO;

public class AptosSDK : ModuleRules
{
	public AptosSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				Path.Combine(ModuleDirectory, "Public")
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				Path.Combine(ModuleDirectory, "Private")
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"HTTP",
				"Json",
				"JsonUtilities"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			SetWindowsDependencies();
		}
	}

	void SetWindowsDependencies()
    {
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Windows"));

		string SodiumLibraryPath		= Path.Combine(ModuleDirectory, "Private", "Windows", "Libraries", "libsodium.lib");
		string SodiumDynamicLibraryPath = Path.Combine(ModuleDirectory, "Private", "Windows", "Libraries", "libsodium.dll");

		//PublicAdditionalLibraries.Add(SodiumLibraryPath);
		//RuntimeDependencies.Add(SodiumDynamicLibraryPath);
		//PublicDelayLoadDLLs.Add("libsodium.dll");
	}
}
