// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetBase.h"
#include "MovingTarget.generated.h"

/**
 * 
 */
UCLASS()
class AIMTRAINER_API AMovingTarget : public ATargetBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
};
