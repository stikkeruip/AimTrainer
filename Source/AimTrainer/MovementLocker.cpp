// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementLocker.h"
#include "AimTrainerGameModeBase.h"
#include "ATCharacterBase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AMovementLocker::AMovementLocker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	StaticMeshComponent->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(StaticMeshComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMovementLocker::StopInput);
	
}

// Called when the game starts or when spawned
void AMovementLocker::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovementLocker::StopInput(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(auto* CharacterBase = Cast<AATCharacterBase>(OtherActor))
	{
		CharacterBase->SetInputLocked(true);

		for(int i = 0; i < 3; i++)
		{
			float xy = FMath::RandRange(-1500, 3000);
			float z = FMath::RandRange(200, 1500);
			FVector Position = FVector(xy, xy, z);
			FRotator Rotation = FRotator(0.f, 0.f, 0.f);
			
			AActor* SpawnedTarget = GetWorld()->SpawnActor(TargetsToSpawn, &Position, &Rotation); //3000 -1500, -1500 3000, 200 1500
			SpawnedTargets.Add(SpawnedTarget);
		}
		Cast<AAimTrainerGameModeBase>(GetWorld()->GetAuthGameMode())->SetGameDuration(GameDuration);
		CharacterBase->EnteredRange();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, Cast<AAimTrainerGameModeBase>(GetWorld()->GetAuthGameMode()), &AAimTrainerGameModeBase::StartGame, GameDuration, false);
	}
}

// Called every frame
void AMovementLocker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

