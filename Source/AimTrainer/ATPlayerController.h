// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ATPlayerController.generated.h"

class UATGameWidget;
class AATCharacterBase; class AAimTrainerGameModeBase;

/**
 * 
 */
UCLASS()
class AIMTRAINER_API AATPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	TSubclassOf<UATGameWidget> GetGameWidget() { return GameWidgetClass; }

protected:

	//void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const override;
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;
	
	virtual void BeginPlay() override;

	void OnJumpAction();

	void Reload();

	void Shoot();

	void StopShoot();

	void SwitchWeapon();

	void MoveForward(float value);
	
	void MoveRight(float value);

	void LookYaw(float value);

	void LookPitch(float value);

	bool CheckCharacterLocked();

	UPROPERTY(EditAnywhere, Category = "Look", BlueprintReadWrite)
	float BaseLookYawRate = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Look", BlueprintReadWrite)
	float BaseLookPitchRate = 90.0f;

	AAimTrainerGameModeBase* GameModeRef = nullptr;
	
	UPROPERTY(Replicated)
	AATCharacterBase* CharacterBase = nullptr;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UATGameWidget> GameWidgetClass;

	FTimerHandle TimerHandle;

public:

	
};
