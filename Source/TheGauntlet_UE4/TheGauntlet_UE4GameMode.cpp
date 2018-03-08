// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TheGauntlet_UE4GameMode.h"
#include "TheGauntlet_UE4HUD.h"
#include "TheGauntlet_UE4Character.h"
#include "UObject/ConstructorHelpers.h"

ATheGauntlet_UE4GameMode::ATheGauntlet_UE4GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATheGauntlet_UE4HUD::StaticClass();
}
