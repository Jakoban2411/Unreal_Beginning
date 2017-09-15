// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Escape_BuildingEditorTarget : TargetRules
{
	public Escape_BuildingEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        bUseUnityBuild = false;
        bUsePCHFiles = false;
        ExtraModuleNames.AddRange( new string[] { "Escape_Building" } );
	}
}
