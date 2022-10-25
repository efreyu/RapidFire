// Rapid Fire Game. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class RapidFireEditorTarget : TargetRules
{
	public RapidFireEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "RapidFire" } );
		
		// macos build fix
        bOverrideBuildEnvironment = true;
        AdditionalCompilerArguments = "-Wno-unused-but-set-variable";
	}
}
