// Fill out your copyright notice in the Description page of Project Settings.


#include "ATCharacterBase.h"

#include "AimTrainerGameModeBase.h"
#include "GunBase.h"
#include "MovementLocker.h"
#include "TargetBase.h"

// Sets default values
AATCharacterBase::AATCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void AATCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<AAimTrainerGameModeBase>(GetWorld()->GetAuthGameMode());
}

void AATCharacterBase::ApplyEffect_Implementation(EEffectType EffectType)
{
	if(bIsUnderEffect) return;

	CurrentEffect = EffectType;
	bIsUnderEffect = true;

	switch (CurrentEffect)
	{
		case EEffectType::POWER:
			GunBaseRef->Damage *= 2;
			break;
		case EEffectType::SLOW:
			bIsLookLock = true;
			break;
		default:
			break;
	}
}

void AATCharacterBase::EndEffect()
{
	bIsUnderEffect = false;
	switch (CurrentEffect)
	{
		case EEffectType::POWER:
			GunBaseRef->Damage /= 2;
			break;
		case EEffectType::SLOW:
			bIsLookLock = false;
			break;
		default:
			break;
	}
}

// Called every frame
void AATCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsUnderEffect)
	{
		if(EffectCooldown > 0)
		{
			EffectCooldown -= DeltaTime;
		}
		else
		{
			bIsUnderEffect = false;
			EffectCooldown = DefaultEffectCooldown;
			EndEffect();
		}
	}

}

// Called to bind functionality to input
void AATCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AATCharacterBase::EnteredRange(AMovementLocker* Range)
{
	CurrentRange = Range;
	GameModeRef->SetCurrentGameState(EGameState::Waiting);
	GameModeRef->DisplayCountdown();
}

void AATCharacterBase::Shoot()
{
	if(GameModeRef->GetCurrentGameState() != EGameState::Playing)
		return;

	GunShot();
	
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	
	FVector LineStart = GetCameraLocation() + GetCameraForward() * 50;
	FVector LineEnd = LineStart + GetCameraRotation().Vector() * 8000.0f;

	GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_Pawn, TraceParams);

	HitActor = HitResult.GetActor();

	if(HitActor && HitActor->ActorHasTag("Target"))
	{
		ATargetBase* HitTarget = Cast<ATargetBase>(HitActor);

		if(HitTarget->GetEffect() != EEffectType::NONE)
		{
			ApplyEffect_Implementation(HitTarget->GetEffect());
		}
		HitActor->Destroy();
	}
}

