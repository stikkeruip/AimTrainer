// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AimTrainerGameModeBase.generated.h"

class AATCharacterBase;
class UATGameInstance;
class UATGameWidget;
class AATGameState;
UCLASS()
class AIMTRAINER_API AAimTrainerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;


private:
	UPROPERTY()
	TMap<APlayerController*, UATGameWidget*> GameWidgets;

	UATGameInstance* GameInstance = nullptr;

	AATGameState* GameState = nullptr;
};
