// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "TargetMovementComponent.generated.h"

class AATGameState;
class AAimTrainerGameModeBase;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AIMTRAINER_API UTargetMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

	UTargetMovementComponent();

protected:
	

	AATGameState* GameState = nullptr;

private:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float TimePassed = 0;

	float TimeToMove;

	FVector LocationToMove;

	FVector InitialLocation;

	void GenTimeToMove() { TimeToMove = FMath::RandRange(1.5, 4.); }

	void GenLocationToMove() { LocationToMove = GetOwner()->GetActorLocation() + FVector(FMath::RandRange(-1500, 2500), 0, 0); }
};
