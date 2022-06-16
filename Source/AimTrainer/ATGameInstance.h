// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AimTrainerGameModeBase.h"
#include "Engine/GameInstance.h"
#include "ATGameInstance.generated.h"

class UATGameWidget;
UCLASS()
class AIMTRAINER_API UATGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	int ActiveTargets = 0;
	
	float GetActiveTargets() { return ActiveTargets; }

private:
	
};
