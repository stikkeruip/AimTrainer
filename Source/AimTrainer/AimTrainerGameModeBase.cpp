// Copyright Epic Games, Inc. All Rights Reserved.


#include "AimTrainerGameModeBase.h"
#include "ATGameWidget.h"
#include "Kismet/GameplayStatics.h"

void AAimTrainerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameState = EGameState::NONE;
}

void AAimTrainerGameModeBase::DisplayCountdown()
{
	if(!GameWidgetClass)
		return;

	for(FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		APlayerController* PC = It->Get();
		if(PC && PC->PlayerState && !MustSpectate(PC))
		{
			UATGameWidget* GameWidget = CreateWidget<UATGameWidget>(PC, GameWidgetClass);
			if(GameWidget)
			{
				GameWidget->AddToPlayerScreen();
				GameWidget->StartCountdown(WaitTime, this);
				GameWidgets.Add(PC, GameWidget);
			}
		}
	}
}

void AAimTrainerGameModeBase::StartGame()
{
	CurrentGameState = EGameState::Playing;
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


