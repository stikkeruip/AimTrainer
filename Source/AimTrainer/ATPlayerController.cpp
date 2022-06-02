// Fill out your copyright notice in the Description page of Project Settings.


#include "ATPlayerController.h"
#include "AimTrainerGameModeBase.h"
#include "ATCharacterBase.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

#pragma optimize("", off)

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

void AATPlayerController::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	DOREPLIFETIME( AATPlayerController, CharacterBase );
}

void AATPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<AAimTrainerGameModeBase>(GetWorld()->GetAuthGameMode());

	if (InputComponent)
	{
		InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AATPlayerController::OnJumpAction);
		InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &AATPlayerController::Shoot);
		InputComponent->BindAction("Shoot", EInputEvent::IE_Released, this, &AATPlayerController::StopShoot);
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

void AATPlayerController::Shoot()
{
	GetWorldTimerManager().SetTimer(TimerHandle, CharacterBase, &AATCharacterBase::Shoot, 0.2, true, 0.);
}

void AATPlayerController::StopShoot()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AATPlayerController::MoveForward(float value)
{
	if(CheckCharacterLocked() || !GetPawn())
		return;
	
	FRotator const ControlSpaceRot = GetControlRotation();

	GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), value);
}

void AATPlayerController::MoveRight(float value)
{
	if(CheckCharacterLocked() || !GetPawn())
		return;
	
	FRotator const ControlSpaceRot = GetControlRotation();

	GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), value);
}

void AATPlayerController::LookYaw(float value)
{
	if(CharacterBase && !CharacterBase->GetLookLock())
	AddYawInput(value * BaseLookYawRate * GetWorld()->GetDeltaSeconds());
}

void AATPlayerController::LookPitch(float value)
{
	if(CharacterBase && !CharacterBase->GetLookLock())
	AddPitchInput(value * BaseLookPitchRate * GetWorld()->GetDeltaSeconds());
}

bool AATPlayerController::CheckCharacterLocked()
{
	if(CharacterBase && CharacterBase->GetInputLocked())
	{
		return true;
	}
	return false;
}
#pragma optimize("", on)