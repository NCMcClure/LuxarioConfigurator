// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Configurator : ModuleRules
{
	public Configurator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "ImageWriteQueue", "RenderCore", "RHI", "Json" });

        string ConfiguratorPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
        
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", System.IO.Path.Combine(ConfiguratorPath, "Configurator_APL.xml"));
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            AdditionalPropertiesForReceipt.Add("IOSPlugin", System.IO.Path.Combine(ConfiguratorPath, "Configurator_UPL.xml"));
		}
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
