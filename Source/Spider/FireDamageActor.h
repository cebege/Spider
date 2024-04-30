// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireDamageActor.generated.h"

UCLASS()
class SPIDER_API AFireDamageActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AFireDamageActor();
	//virtual void PostActorCreated() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(EditAnywhere)
	//	UDealDamageComponent* DealDamageComponent;

	UPROPERTY(EditAnywhere, NoClear)
		UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere)
		float ToggleTime = 5.0f;

	float CurrentTime = 0.0f;

};
