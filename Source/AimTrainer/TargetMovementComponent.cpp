// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetMovementComponent.h"

#include "ATGameState.h"

UTargetMovementComponent::UTargetMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTargetMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<AATGameState>(GetWorld()->GetGameState());

	InitialLocation = GetOwner()->GetActorLocation();
	
	GenLocationToMove();

	GenTimeToMove();
}

void UTargetMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(GameState->GetCurrentGameState() == EGameState::Playing)
	{
		TimePassed += DeltaTime;
		if(TimePassed < TimeToMove)
		{
			FVector CurrentLocation = FMath::Lerp(InitialLocation, LocationToMove, FMath::Clamp(TimePassed/TimeToMove, 0., 1.));
			GetOwner()->SetActorLocation(CurrentLocation);
		}
		else
		{
			InitialLocation = GetOwner()->GetActorLocation();
			GenLocationToMove();
			GenTimeToMove();
			TimePassed = 0;
		}
	}
}
