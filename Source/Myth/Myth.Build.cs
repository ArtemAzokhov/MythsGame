// Myth Game, All Rights Reserved.

using UnrealBuildTool;

public class Myth : ModuleRules
{
	public Myth(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore",
            "EnhancedInput",
            "UMG"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange(new string[] 
        {
            "Myth/Public/Components",
            "Myth/Public/Dev",
            "Myth/Public/Player",
            "Myth/Public/UI"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
