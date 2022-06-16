// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MovementLocker.generated.h"

class AAimTrainerGameModeBase; class AATGameState; class UATGameInstance;
UCLASS()
class AIMTRAINER_API AMovementLocker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovementLocker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> TargetsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Details")
	float WaitTime = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GameDurationML = 5;
	
	UFUNCTION()
	void StopInput(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle TimerHandle;

	int MaxTargets = 5;

	float SpawnWaitTime = 1.5f;
	
	float LastSpawnTime = 0.f;

	AAimTrainerGameModeBase* GameModeRef;

	AATGameState* GameState;

	UATGameInstance* GameInstance;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
