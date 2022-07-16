// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"

#include "ATCharacterBase.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunBase::Reload()
{
	CurrentBullets = MaxBullets;
}

AActor* AGunBase::Shoot()
{
	if(OwningCharacter->bIsReloading || OwningCharacter->bIsSwitching || CurrentBullets == 0)
		return nullptr;

	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	
	FVector LineStart = OwningCharacter->GetCameraLocation() + OwningCharacter->GetCameraForward() * 50;
	FVector LineEnd = LineStart + OwningCharacter->GetCameraRotation().Vector() * 8000.0f;

	GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_Pawn, TraceParams);

	CurrentBullets--;
	
	if(HitResult.GetActor())
		return HitResult.GetActor();

	return nullptr;
}

