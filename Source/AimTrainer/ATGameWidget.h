// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ATGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class AIMTRAINER_API UATGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void StartCountdown(float CountdownTime, class AAimTrainerGameModeBase* GameMode);

	UFUNCTION(BlueprintImplementableEvent)
	void LevelComplete();
	
};
