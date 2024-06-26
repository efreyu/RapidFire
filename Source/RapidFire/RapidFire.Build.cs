// Rapid Fire Game.

using UnrealBuildTool;

public class RapidFire : ModuleRules
{
    public RapidFire(ReadOnlyTargetRules Target)
        : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara" });

        PrivateDependencyModuleNames.AddRange(new string[] {});

        PublicIncludePaths.AddRange(new string[] {
            "RapidFire/Public/Player",
            "RapidFire/Public/Components",
            "RapidFire/Public/Dev",
            "RapidFire/Public/Weapons",
            "RapidFire/Public/Weapons/Components",
            "RapidFire/Public/UI",
            "RapidFire/Public/Animations"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
