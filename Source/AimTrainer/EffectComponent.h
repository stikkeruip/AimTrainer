// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpInterface.h"
#include "Components/ActorComponent.h"
#include "EffectComponent.generated.h"


class AATCharacterBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIMTRAINER_API UEffectComponent : public UActorComponent, public IPowerUpInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bIsUnderEffect = false;

	float DefaultEffectCooldown = 3.;

	float EffectCooldown = 3.;

	EEffectType CurrentEffect = EEffectType::NONE;

	void ApplyEffect(EEffectType EffectType) override;

	void EndEffect();

	AATCharacterBase* C = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
