// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MenuButton.generated.h"

class AATCharacterBase;
/**
 * 
 */
UCLASS()
class AIMTRAINER_API AMenuButton : public AStaticMeshActor
{
	GENERATED_BODY()

	
public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnHit(AATCharacterBase* Character);
};
