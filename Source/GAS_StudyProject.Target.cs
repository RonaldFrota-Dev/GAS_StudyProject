// Ronald Symon Frota e Frota All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class GAS_StudyProjectTarget : TargetRules
{
	public GAS_StudyProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "GAS_StudyProject" } );
	}
}
