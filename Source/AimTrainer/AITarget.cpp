// Fill out your copyright notice in the Description page of Project Settings.


#include "AITarget.h"

// Sets default values
AAITarget::AAITarget()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	StaticMeshComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAITarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAITarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAITarget::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

