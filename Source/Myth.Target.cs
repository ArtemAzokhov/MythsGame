// Myth Game, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MythTarget : TargetRules
{
	public MythTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Myth" } );
	}
}
