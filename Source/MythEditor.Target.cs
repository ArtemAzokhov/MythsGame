// Myth Game, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MythEditorTarget : TargetRules
{
	public MythEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Myth" } );
	}
}
