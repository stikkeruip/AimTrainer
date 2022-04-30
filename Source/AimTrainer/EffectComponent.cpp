// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectComponent.h"

#include "ATCharacterBase.h"

// Sets default values for this component's properties
UEffectComponent::UEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	C = Cast<AATCharacterBase>(GetOwner());
}


void UEffectComponent::ApplyEffect(EEffectType EffectType)
{
	if(bIsUnderEffect) return;

	CurrentEffect = EffectType;
	bIsUnderEffect = true;

	switch (CurrentEffect)
	{
	case EEffectType::POWER:
		C->SetDamage(true);
		break;
	case EEffectType::SLOW:
		C->SetLookLock(true);
		break;
	default:
		break;
	}
}

void UEffectComponent::EndEffect()
{
	bIsUnderEffect = false;
	switch (CurrentEffect)
	{
	case EEffectType::POWER:
		C->SetDamage(false);
		break;
	case EEffectType::SLOW:
		C->SetLookLock(false);
		break;
	default:
		break;
	}
}

// Called every frame
void UEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bIsUnderEffect)
	{
		if(EffectCooldown > 0)
		{
			EffectCooldown -= DeltaTime;
		}
		else
		{
			bIsUnderEffect = false;
			EffectCooldown = DefaultEffectCooldown;
			EndEffect();
		}
	}
}

