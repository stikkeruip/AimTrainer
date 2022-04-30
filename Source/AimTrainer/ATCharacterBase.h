// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATPlayerController.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ATCharacterBase.generated.h"

class AAimTrainerGameModeBase; class AMovementLocker; class AGunBase;
UCLASS()
class AIMTRAINER_API AATCharacterBase : public ACharacter
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

	UFUNCTION(BlueprintImplementableEvent)
	void GunShot();

	UPROPERTY(BlueprintReadOnly)
	AActor* HitActor = nullptr;

	AMovementLocker* CurrentRange = nullptr;

	bool isInputLocked = false;

	bool bIsLookLock = false;

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

	void Shoot();

	bool GetLookLock() { return bIsLookLock; }

	AAimTrainerGameModeBase* GameModeRef = nullptr;

	UPROPERTY(BlueprintReadWrite)
	AGunBase* GunBaseRef;

	void SetLookLock(bool value) { bIsLookLock = value; }

	void SetDamage(bool value);
};
