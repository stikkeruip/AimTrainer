// Copyright Epic Games, Inc. All Rights Reserved.


#include "AimTrainerGameModeBase.h"

#include "ATGameInstance.h"
#include "ATGameState.h"
#include "ATGameWidget.h"
#include "Kismet/GameplayStatics.h"

void AAimTrainerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	GameInstance = Cast<UATGameInstance>(GetGameInstance());
	GameState = Cast<AATGameState>(GetWorld()->GetGameState());
}


