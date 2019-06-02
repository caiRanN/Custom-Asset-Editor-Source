// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AssetEditorTutorialEditorTarget : TargetRules
{
	public AssetEditorTutorialEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("AssetEditorTutorial");
        ExtraModuleNames.Add("CustomAssetEditor");
    }
}
