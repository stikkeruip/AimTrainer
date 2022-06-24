// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "gamestatetest.generated.h"

/**
 * 
 */
UCLASS()
class AIMTRAINER_API Agamestatetest : public AGameStateBase
{
	GENERATED_BODY()


	Agamestatetest();

	virtual void Tick(float DeltaTime) override;
};
