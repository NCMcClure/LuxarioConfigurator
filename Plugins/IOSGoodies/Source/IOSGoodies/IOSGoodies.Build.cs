// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class IOSGoodies : ModuleRules
{
	public IOSGoodies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] 
			{
#if UE_4_20_OR_LATER
				Path.Combine (ModuleDirectory, "Public")
#else
				"IOSGoodies/Public"
#endif
				// ... add other public include paths required here ...
			}
		);		
		
		PrivateIncludePaths.AddRange(
			new string[] {
#if UE_4_20_OR_LATER
				Path.Combine (ModuleDirectory, "Private")
#else
				"IOSGoodies/Private"
#endif
				// ... add other private include paths required here ...
			}
		);
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Engine",
				"Core",
				"CoreUObject"
				// ... add other public dependencies that you statically link with here ...
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
		);
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);

		if (Target.Platform == UnrealTargetPlatform.IOS)
        {
#if UE_4_20_OR_LATER
			PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/IOS"));
#else
			PrivateIncludePaths.AddRange(
				new string[]
				{
					"IOSGoodies/Private/IOS"
					// ... add other private include paths required here ...
				}
			);
#endif
			PublicFrameworks.AddRange (
				new string[]
				{
					"MessageUI",
					"StoreKit",
					"AVFoundation",
                    "Photos",
                    "EventKit",
                    "Contacts"
				}
			);

			PrivateDependencyModuleNames.AddRange (new string[] { "Launch" });
			string PluginPath = Utils.MakePathRelativeTo (ModuleDirectory, Target.RelativeEnginePath);

#if UE_4_19_OR_LATER
			AdditionalPropertiesForReceipt.Add ("IOSPlugin", Path.Combine (PluginPath, "IOSGoodies_UPL.xml"));
#else
			AdditionalPropertiesForReceipt.Add (new ReceiptProperty ("IOSPlugin", Path.Combine (PluginPath, "IOSGoodies_UPL.xml")));
#endif
		}
	}
}
