// Ronald Symon Frota e Frota All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class GAS_StudyProjectEditorTarget : TargetRules
{
	public GAS_StudyProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "GAS_StudyProject" } );
	}
}
