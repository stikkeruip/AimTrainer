// Fill out your copyright notice in the Description page of Project Settings.


#include "ATGameState.h"

#include "AimTrainerGameModeBase.h"
#include "ATGameWidget.h"
#include "ATPlayerController.h"
#include "Net/UnrealNetwork.h"

void AATGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams SharedParams;

	SharedParams.bIsPushBased = true;
	//SharedParams.Condition = COND_SkipOwner;

	DOREPLIFETIME_WITH_PARAMS_FAST(AATGameState, CurrentGameState, SharedParams);
}

void AATGameState::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameState = EGameState::Waiting;

	GameModeRef = Cast<AAimTrainerGameModeBase>(GetWorld()->GetAuthGameMode());
}

void AATGameState::DisplayLocalCountdown()
{
	AATPlayerController* PC = Cast<AATPlayerController>(GetWorld()->GetFirstPlayerController());
	if(!PC)
		return;
	
	TSubclassOf<UATGameWidget> GameWidgetClass = PC->GetGameWidget();

	if(PC->PlayerState)
	{
		UATGameWidget* GameWidget = CreateWidget<UATGameWidget>(PC, GameWidgetClass);
		if(GameWidget)
		{
			GameWidget->AddToPlayerScreen();
			GameWidget->StartCountdown(GameModeRef->GetWaitTime());
		}
	}
}

void AATGameState::SetCurrentGameState(EGameState State)
{
	EGameState OldState = CurrentGameState;
	CurrentGameState = State;
	OnRep_GameState(OldState);
}

void AATGameState::AimRangeDone()
{

	AATPlayerController* PC = Cast<AATPlayerController>(GetWorld()->GetFirstPlayerController());
	if(!PC)
		return;
	
	TSubclassOf<UATGameWidget> GameWidgetClass = PC->GetGameWidget();

	if(PC->PlayerState)
	{
		UATGameWidget* GameWidget = CreateWidget<UATGameWidget>(PC, GameWidgetClass);
		if(GameWidget)
		{
			GameWidget->AddToPlayerScreen();
			GameWidget->LevelComplete();

			FInputModeUIOnly InputMode;
			PC->SetInputMode(InputMode);
			PC->SetShowMouseCursor(true);
		}
	}

	CurrentGameState = EGameState::GameOver;
}

void AATGameState::AddPlayer(AATCharacterBase* Player)
{
	if(CurrentGameState != EGameState::Waiting)
		return;

	
	//Check game state
	//If playing, ignore
	//If countdown, ignore
	//If waiting
	//Lock all players in and teleport to locker
	//Set state to countdown
}

void AATGameState::OnRep_GameState(const EGameState& OldGameState)
{
	switch (CurrentGameState)
	{
		case EGameState::Countdown:
			DisplayLocalCountdown();
			break;

		default:
			break;
	}
	//If countdown, grab local player controller, display countdown
	//Check authority
}
