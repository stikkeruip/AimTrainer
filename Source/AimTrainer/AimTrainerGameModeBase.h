// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AimTrainerGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	NONE		UMETA(DisplayName = "NONE"),
	Waiting		UMETA(DisplayName = "Waiting"),
	Playing		UMETA(DisplayName = "Playing"),
	Paused		UMETA(DisplayName = "Paused"),
	GameOver	UMETA(DisplayName = "GameOver"),
};

class UATGameWidget;
UCLASS()
class AIMTRAINER_API AAimTrainerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const { return CurrentGameState; }

	void SetCurrentGameState(EGameState State) { CurrentGameState = State; }

	void DisplayCountdown();

	void StartGame();

	void SetGameDuration(float value) { GameDuration = value;}

private:
	UPROPERTY(VisibleAnywhere, Category = "States")
	EGameState CurrentGameState = EGameState::NONE;

	UPROPERTY()
	UATGameWidget* GameWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UATGameWidget> GameWidgetClass;

	float GameDuration;

	APlayerController* PC = nullptr;
};
