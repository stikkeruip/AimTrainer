// Fill out your copyright notice in the Description page of Project Settings.


#include "ATGameState.h"

#include "AimTrainerGameModeBase.h"
#include "ATGameWidget.h"
#include "ATPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AATGameState::AATGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

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

	NumPlayers = GetWorld()->GetNumPlayerControllers();
}

void AATGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetWorld() && GetWorld()->GetTimeSeconds() - LastSpawnTime > SpawnWaitTime)
	{
		if(ActiveTargets < MaxTargets)
		{
			float xy = FMath::RandRange(-1500, 3000);
			float z = FMath::RandRange(200, 1500);
			FVector Position = FVector(xy, xy, z);
			FRotator Rotation = FRotator(0.f, 0.f, 0.f);
		
			GetWorld()->SpawnActor(SelectedTarget, &Position, &Rotation);

			LastSpawnTime = GetWorld()->GetTimeSeconds();
			ActiveTargets++;
		}
	}
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
			GameWidget->StartWaitCountdown(WaitTime);
		}
	}
}

void AATGameState::SetCurrentGameState(EGameState State)
{
	CurrentGameState = State;
	OnRep_GameState();
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
	bIsGamePlaying = false;
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

void AATGameState::PlayerEnteredLocker(AATCharacterBase* Player)
{
	PlayersReady++;
	
	FTimerHandle TimerHandle;
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "SetCurrentGameState", EGameState::Playing);

	if(PlayersReady == NumPlayers)
	{
		SetCurrentGameState(EGameState::Countdown);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, WaitTime, false);
	}
}

void AATGameState::StartTraining()
{
	bIsGamePlaying = true;

	CheckTargetSelected();
}

void AATGameState::OnRep_GameState()
{
	switch (CurrentGameState)
	{
		case EGameState::Countdown:
			DisplayLocalCountdown();
			break;

		case EGameState::Restart:
			RestartGame();
			break;

		case EGameState::Waiting:
			RemoveMenu();
			break;

		case EGameState::Playing:
			StartTraining();
			break;

		case EGameState::GameOver:
			AimRangeDone();
			break;
			
		default:
			break;
	}
	//If countdown, grab local player controller, display countdown
	//Check authority
}
