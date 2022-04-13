// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ATPlayerController.generated.h"

class AATCharacterBase; class AAimTrainerGameModeBase;

/**
 * 
 */
UCLASS()
class AIMTRAINER_API AATPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;
	
	virtual void BeginPlay() override;

	void OnJumpAction();

	void DisableLock();

	void Shoot();

	void MoveForward(float value);
	
	void MoveRight(float value);

	void LookYaw(float value);

	void LookPitch(float value);

	bool CheckCharacterLocked();

	UPROPERTY(EditAnywhere, Category = "Look", BlueprintReadWrite)
	float BaseLookYawRate = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Look", BlueprintReadWrite)
	float BaseLookPitchRate = 90.0f;

	AAimTrainerGameModeBase* GameModeRef;
	
	UPROPERTY()
	AATCharacterBase* CharacterBase = nullptr;

public:

	
};
