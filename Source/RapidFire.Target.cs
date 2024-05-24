// Rapid Fire Game.

using UnrealBuildTool;
using System.Collections.Generic;

public class RapidFireTarget : TargetRules
{
    public RapidFireTarget(TargetInfo Target)
        : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;

        ExtraModuleNames.AddRange(new string[] { "RapidFire" });
    }
}
