// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetHitInterface.h"
#include "PowerUpInterface.h"
#include "GameFramework/Actor.h"
#include "TargetBase.generated.h"

UCLASS()
class AIMTRAINER_API ATargetBase : public AActor, public ITargetHitInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	EEffectType EffectType = EEffectType::NONE;

	void OnHit(AActor* HitInstigator) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EEffectType GetEffect() { return EffectType; }
};
