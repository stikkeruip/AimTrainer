// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveMenu.h"

// Sets default values
AInteractiveMenu::AInteractiveMenu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));

	Base->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractiveMenu::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractiveMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

