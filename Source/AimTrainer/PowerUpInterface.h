// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PowerUpInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPowerUpInterface : public UInterface
{
	GENERATED_BODY()
};

UENUM(BlueprintType)
enum class EEffectType : uint8
{
	NONE		UMETA(DisplayName = "None"),
	SLOW		UMETA(DisplayName = "Slow"),
	POWER		UMETA(DisplayName = "Power"),
};

class AIMTRAINER_API IPowerUpInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(Category = "Interact")
	virtual void ApplyEffect(EEffectType EffectType) PURE_VIRTUAL(IPowerUpInterface::ApplyEffect, { /*Empty*/ });
};
