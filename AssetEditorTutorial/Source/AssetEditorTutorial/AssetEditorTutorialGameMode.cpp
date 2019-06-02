// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AssetEditorTutorialGameMode.h"
#include "AssetEditorTutorialHUD.h"
#include "AssetEditorTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAssetEditorTutorialGameMode::AAssetEditorTutorialGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAssetEditorTutorialHUD::StaticClass();
}
