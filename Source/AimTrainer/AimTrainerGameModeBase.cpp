// Copyright Epic Games, Inc. All Rights Reserved.


#include "AimTrainerGameModeBase.h"
#include "ATGameWidget.h"
#include "Kismet/GameplayStatics.h"

void AAimTrainerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameState = EGameState::NONE;
}

void AAimTrainerGameModeBase::AimRangeDone()
{
	SetCurrentGameState(EGameState::Waiting);
	for(auto i : GameWidgets)
	{
		if(i.Value)
		{
			i.Value->LevelComplete();
		}
		if(i.Key)
		{
			FInputModeUIOnly InputMode;
			i.Key->SetInputMode(InputMode);
			i.Key->SetShowMouseCursor(true);
		}
	}
	
}


