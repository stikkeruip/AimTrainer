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
	GameOver	UMETA(DisplayName = "GameOver"),
};

UCLASS()
class AIMTRAINER_API AATGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const { return CurrentGameState; }

	UFUNCTION()
	void SetCurrentGameState(EGameState State);

	UFUNCTION(BlueprintCallable)
	void AimRangeDone();

	void DisplayCountdown();

	void AddPlayer(AATCharacterBase* Player);

	void DisplayLocalCountdown();

private:
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_GameState, Category = "States")
	EGameState CurrentGameState = EGameState::NONE;

	UFUNCTION()
	void OnRep_GameState(const EGameState& OldGameState);

	TArray<AATCharacterBase*> Players;
	
	AAimTrainerGameModeBase* GameModeRef = nullptr;

	virtual void BeginPlay() override;
};
