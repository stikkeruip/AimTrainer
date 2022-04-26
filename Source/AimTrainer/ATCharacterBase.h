// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATPlayerController.h"
#include "PowerUpInterface.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ATCharacterBase.generated.h"

class AAimTrainerGameModeBase; class AMovementLocker; class AGunBase;
UCLASS()
class AIMTRAINER_API AATCharacterBase : public ACharacter, public IPowerUpInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AATCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UCameraComponent* CameraComponent;

	UFUNCTION(BlueprintCallable)
	AATPlayerController* GetATPlayerController() { return Cast<AATPlayerController>(GetController()); }

	UFUNCTION(BlueprintImplementableEvent)
	void GunShot();

	UPROPERTY(BlueprintReadOnly)
	AActor* HitActor = nullptr;

	AMovementLocker* CurrentRange = nullptr;

	bool isInputLocked = false;

	void ApplyEffect_Implementation(EEffectType EffectType, bool bIsBuff) override;

	void EndEffect();

	bool bIsUnderEffect = false;

	bool bIsEffectBuff = false;

	float DefaultEffectCooldown = 3.;

	float EffectCooldown = 0.;

	EEffectType CurrentEffect = EEffectType::NONE;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetInputLocked(bool val) { isInputLocked = val; }

	bool GetInputLocked() { return isInputLocked; }

	FVector GetCameraLocation() { return CameraComponent->GetComponentLocation(); }
	
	FRotator GetCameraRotation() { return CameraComponent->GetComponentRotation(); }
	
	FVector GetCameraForward() { return CameraComponent->GetForwardVector(); }

	void EnteredRange(AMovementLocker* Range);

	void TargetShot(AActor* Target);

	void Shoot();

	AAimTrainerGameModeBase* GameModeRef = nullptr;

	UPROPERTY(BlueprintReadWrite)
	AGunBase* GunBaseRef;
};
