// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetBase.h"

#include "EffectComponent.h"
#include "PowerUpInterface.h"

// Sets default values
ATargetBase::ATargetBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATargetBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATargetBase::OnHit(AActor* HitInstigator)
{
	IPowerUpInterface* I = Cast<IPowerUpInterface>(HitInstigator->FindComponentByClass<UEffectComponent>());

	if(I)
	{
		I->ApplyEffect(EffectType);
	}
}

// Called every frame
void ATargetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

