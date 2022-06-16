// Copyright Epic Games, Inc. All Rights Reserved.


#include "AimTrainerGameModeBase.h"

#include "ATGameInstance.h"
#include "ATGameState.h"
#include "ATGameWidget.h"
#include "Kismet/GameplayStatics.h"

void AAimTrainerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	GameInstance = Cast<UATGameInstance>(GetGameInstance());
	GameState = Cast<AATGameState>(GetWorld()->GetGameState());
}

void AAimTrainerGameModeBase::PlayerEnteredLocker(AATCharacterBase* Player)
{
	FTimerHandle TimerHandle;
	FTimerDelegate Delegate;
	Delegate.BindUFunction(GameState, "SetCurrentGameState", EGameState::Playing);

	GameState->SetCurrentGameState(EGameState::Countdown);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, WaitTime, false);
}


