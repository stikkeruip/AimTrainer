// Fill out your copyright notice in the Description page of Project Settings.


#include "ATCharacterBase.h"

#include "AimTrainerGameModeBase.h"
#include "GunBase.h"
#include "MovementLocker.h"

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

// Called every frame
void AATCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void AATCharacterBase::TargetShot(AActor* Target)
{
	CurrentRange->DestroyTarget(Target);
}

void AATCharacterBase::Shoot()
{
	if(GameModeRef->GetCurrentGameState() != EGameState::Playing)
		return;

	GunShot();
	
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	
	FVector LineStart = GetCameraLocation() + GetCameraForward() * 50;
	FVector LineEnd = LineStart + GetCameraRotation().Vector() * 4000.0f;

	GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_Pawn, TraceParams);

	AActor* HitActor = HitResult.GetActor();

	if(HitActor && HitActor->ActorHasTag("Target"))
	{
		TargetShot(HitActor);
		HitActor->Destroy();
	}
}

