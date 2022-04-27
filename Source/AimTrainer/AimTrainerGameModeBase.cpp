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
	
	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	GameWidget = CreateWidget<UATGameWidget>(PC, GameWidgetClass);
	GameWidget->AddToViewport();
	GameWidget->StartCountdown(WaitTime, this);
}

void AAimTrainerGameModeBase::StartGame()
{
	CurrentGameState = EGameState::Playing;
}

void AAimTrainerGameModeBase::AimRangeDone()
{
	SetCurrentGameState(EGameState::Waiting);
	GameWidget->LevelComplete();
	FInputModeUIOnly InputMode;
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(true);
}


