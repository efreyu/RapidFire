// Rapid Fire Game.

using UnrealBuildTool;
using System.Collections.Generic;

public class RapidFireEditorTarget : TargetRules
{
	public RapidFireEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "RapidFire" } );
	}
}
