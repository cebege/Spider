// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

class ASpiderCharacter;

UCLASS()
class SPIDER_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	virtual void BeginPlay() override;

	ASpiderCharacter* Character = nullptr;

private:

	UPROPERTY(EditAnywhere, Category = "Combat")
		float FireRange = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float FireRate = 2.f;

	FTimerHandle FireRateTimerHandle;

	void CheckFireCondition();
	bool InFireRange();
	
};
