// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MovementLocker.generated.h"

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

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TargetsToSpawn;

	UPROPERTY(EditAnywhere, Category = "Game Details")
	float GameDuration = 3.f;

	UFUNCTION()
	void StopInput(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	TArray<AActor*> SpawnedTargets;

	FTimerHandle TimerHandle;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestroyTarget (AActor* Target);

};
