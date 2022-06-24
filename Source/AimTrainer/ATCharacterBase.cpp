// Fill out your copyright notice in the Description page of Project Settings.


#include "ATCharacterBase.h"

#include "GunBase.h"
#include "MenuButton.h"
#include "TargetBase.h"
#include "Net/UnrealNetwork.h"

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

void AATCharacterBase::Shoot()
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	
	FVector LineStart = GetCameraLocation() + GetCameraForward() * 50;
	FVector LineEnd = LineStart + GetCameraRotation().Vector() * 8000.0f;

	GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_Pawn, TraceParams);

	HitActor = HitResult.GetActor();

	GunShot();
	
	ITargetHitInterface* I = Cast<ITargetHitInterface>(HitActor);
	
	if(I)
	{
		I->OnHit(this);
		return;
	}

	AMenuButton* M = Cast<AMenuButton>(HitActor);
	if(M)
	{
		M->OnHit(this);
	}
}

void AATCharacterBase::SetDamage(bool value)
{
	GunBaseRef->Damage = value ? GunBaseRef->Damage *= 2 : GunBaseRef->Damage /= 2;
}

