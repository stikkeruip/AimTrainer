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
	bool bIsAuthority = HasAuthority();
	
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	
	if(!Character)
		return;
	
	bool bIsLocallyControlled = Character->IsLocallyControlled();
	
	if(!bIsAuthority && !bIsLocallyControlled)
		return;
	
	if(auto* CharacterBase = Cast<AATCharacterBase>(OtherActor))
	{
		if(bIsLocallyControlled)
		{
			CharacterBase->SetInputLocked(true);
		}
		if(bIsAuthority)
		{
			GameState->PlayerEnteredLocker(CharacterBase);	
		}
	}
}

