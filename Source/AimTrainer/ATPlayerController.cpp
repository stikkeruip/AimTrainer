// Fill out your copyright notice in the Description page of Project Settings.


#include "ATPlayerController.h"

#include "AimTrainerGameModeBase.h"
#include "ATCharacterBase.h"

#include "GameFramework/Character.h"

void AATPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	CharacterBase = Cast<AATCharacterBase>(InPawn);
}

void AATPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	
	CharacterBase = nullptr;
}


void AATPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<AAimTrainerGameModeBase>(GetWorld()->GetAuthGameMode());

	if (InputComponent)
	{
		InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AATPlayerController::OnJumpAction);
		InputComponent->BindAction("EnableMove", EInputEvent::IE_Pressed, this, &AATPlayerController::DisableLock);
		InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &AATPlayerController::Shoot);
		InputComponent->BindAxis("Forward", this, &AATPlayerController::MoveForward);
		InputComponent->BindAxis("Right", this, &AATPlayerController::MoveRight);
		InputComponent->BindAxis("Yaw", this, &AATPlayerController::LookYaw);
		InputComponent->BindAxis("Pitch", this, &AATPlayerController::LookPitch);
	}
}

void AATPlayerController::OnJumpAction()
{
	if (GetCharacter())
	{
		GetCharacter()->Jump();
	}
}

void AATPlayerController::DisableLock()
{
	if(CharacterBase)
	{
		CharacterBase->SetInputLocked(false);
	}
}

void AATPlayerController::Shoot()
{
	CharacterBase->Shoot();
}

void AATPlayerController::MoveForward(float value)
{
	if(CheckCharacterLocked())
		return;
	
	FRotator const ControlSpaceRot = GetControlRotation();

	GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), value);
}

void AATPlayerController::MoveRight(float value)
{
	if(CheckCharacterLocked())
		return;
	
	FRotator const ControlSpaceRot = GetControlRotation();

	GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), value);
}

void AATPlayerController::LookYaw(float value)
{
	AddYawInput(value * BaseLookYawRate * GetWorld()->GetDeltaSeconds());
}

void AATPlayerController::LookPitch(float value)
{
	AddPitchInput(value * BaseLookPitchRate * GetWorld()->GetDeltaSeconds());
}

bool AATPlayerController::CheckCharacterLocked()
{
	if(CharacterBase->GetInputLocked())
	{
		return true;
	}
	return false;
}
