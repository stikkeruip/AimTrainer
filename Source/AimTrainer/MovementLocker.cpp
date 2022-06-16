// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementLocker.h"
#include "AimTrainerGameModeBase.h"
#include "ATCharacterBase.h"
#include "ATGameInstance.h"
#include "ATGameState.h"

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

	GameModeRef = Cast<AAimTrainerGameModeBase>(GetWorld()->GetAuthGameMode());

	GameState = Cast<AATGameState>(GetWorld()->GetGameState());

	GameInstance = Cast<UATGameInstance>(GetGameInstance());
}

void AMovementLocker::StopInput(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!HasAuthority())
		return;
	
	if(auto* CharacterBase = Cast<AATCharacterBase>(OtherActor))
	{
		CharacterBase->SetInputLocked(true);
		GameModeRef->SetWaitTime(WaitTime);
		GameModeRef->PlayerEnteredLocker(CharacterBase);
	}
}

// Called every frame
void AMovementLocker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GameState && GameState->GetCurrentGameState() == EGameState::Playing)
	{
		if(GetWorld() && GetWorld()->GetTimeSeconds() - LastSpawnTime > SpawnWaitTime)
		{
			if(GameInstance->ActiveTargets < MaxTargets)
			{
				float xy = FMath::RandRange(-1500, 3000);
				float z = FMath::RandRange(200, 1500);
				FVector Position = FVector(xy, xy, z);
				FRotator Rotation = FRotator(0.f, 0.f, 0.f);
			
				GetWorld()->SpawnActor(GameModeRef->SelectedTarget, &Position, &Rotation);

				LastSpawnTime = GetWorld()->GetTimeSeconds();
				GameInstance->ActiveTargets++;
			}
		}
	}
}

