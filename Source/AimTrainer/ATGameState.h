// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATCharacterBase.h"
#include "AimTrainerGameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "ATGameState.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	NONE		UMETA(DisplayName = "NONE"),
	Waiting		UMETA(DisplayName = "Waiting"),
	Countdown	UMETA(DisplayName = "Countdown"),
	Playing		UMETA(DisplayName = "Playing"),
	Paused		UMETA(DisplayName = "Paused"),
	Restart		UMETA(DisplayName = "Restart"),
	GameOver	UMETA(DisplayName = "GameOver"),
};

UCLASS()
class AIMTRAINER_API AATGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	AATGameState();
	
	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const { return CurrentGameState; }
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentGameState(EGameState State);

	UFUNCTION(BlueprintImplementableEvent)
	void RestartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void CheckTargetSelected();
	
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<AActor> SelectedTarget;

	UPROPERTY(BlueprintReadWrite)
	bool bIsGamePlaying = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Details")
	float WaitTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GameDurationML;

	void AddPlayer(AATCharacterBase* Player);

	void DisplayLocalCountdown();

	void PlayerEnteredLocker(AATCharacterBase* Player);

	void SetWaitTime(float value) { WaitTime = value;}

	void StartTraining();

	float GetWaitTime() { return WaitTime; }

	bool GetIsTarget() { return bIsTarget; }

	void AimRangeDone();

	void TargetHit() { ActiveTargets--; }

	virtual void Tick(float DeltaTime) override;

private:
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_GameState, Category = "States")
	EGameState CurrentGameState = EGameState::NONE;

	UFUNCTION()
	void OnRep_GameState();

	TArray<AATCharacterBase*> Players;
	
	AAimTrainerGameModeBase* GameModeRef = nullptr;

	virtual void BeginPlay() override;

	int ActiveTargets = 0;

	bool bIsTarget = false;

	int MaxTargets = 5;

	float SpawnWaitTime = 1.5f;
	
	float LastSpawnTime = 0.f;

	int NumPlayers;

	int PlayersReady = 0;
};
