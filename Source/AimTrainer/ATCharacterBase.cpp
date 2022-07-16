// Fill out your copyright notice in the Description page of Project Settings.


#include "ATCharacterBase.h"

#include "ATGameState.h"
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

	GameState = Cast<AATGameState>(GetWorld()->GetGameState());
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
	HitActor = GunBaseRef->Shoot();

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
		return;
	}

	if(GameState->GetCurrentGameState() == EGameState::Playing)
		GameState->TargetMissed();
	
}

void AATCharacterBase::Reload()
{
	if(bIsSwitching)
		return;
	
	bIsReloading = true;
	GunBaseRef->Reload();
}


void AATCharacterBase::SetDamage(bool value)
{
	GunBaseRef->Damage = value ? GunBaseRef->Damage *= 2 : GunBaseRef->Damage /= 2;
}

