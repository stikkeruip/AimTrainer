// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TextRenderActor.h"
#include "GameFramework/Actor.h"
#include "InteractiveMenu.generated.h"

UCLASS()
class AIMTRAINER_API AInteractiveMenu : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveMenu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
