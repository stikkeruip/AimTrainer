// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ATCharacterBase.generated.h"

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

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere)
    UCameraComponent* CameraComponent;

	bool isInputLocked = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetInputLocked(bool val) { isInputLocked = val; }

	bool GetInputLocked() { return isInputLocked; }

	FVector GetCameraLocation() { return CameraComponent->GetComponentLocation(); }
	FRotator GetCameraRotation() { return CameraComponent->GetComponentRotation(); }

};
