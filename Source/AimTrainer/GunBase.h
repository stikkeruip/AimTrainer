// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

class AATCharacterBase;
UCLASS()
class AIMTRAINER_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* GunBlast;

	UPROPERTY(BlueprintReadWrite)
	AATCharacterBase* OwningCharacter;

	const int MaxBullets = 30;
	
	int CurrentBullets = 30;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	float Damage = 50.;

	void Reload();

	AActor* Shoot();
};
