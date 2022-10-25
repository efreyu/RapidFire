// Rapid Fire Game. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class RapidFireTarget : TargetRules
{
	public RapidFireTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "RapidFire" } );
		// macos build fix
        bOverrideBuildEnvironment = true;
        AdditionalCompilerArguments = "-Wno-unused-but-set-variable";
	}
}
