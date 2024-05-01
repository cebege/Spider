// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DamageHandlerComponent.h"

// Sets default values
ASpiderCharacter::ASpiderCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	DamageHandlerComponent = CreateDefaultSubobject<UDamageHandlerComponent>(TEXT("DamageHandlerComponent"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASpiderCharacter::BeginPlay()
{
	Super::BeginPlay();

	PC = GetWorld()->GetFirstPlayerController();

}

// Called every frame
void ASpiderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpiderCharacter::SetOnFire(float BaseDamage, float DamageTotalTime, float TakeDamageInterval)
{
	if (DamageHandlerComponent)
	{
		DamageHandlerComponent->TakeFireDamage(BaseDamage, DamageTotalTime, TakeDamageInterval);
	}
}

// Called to bind functionality to input
void ASpiderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	FInputActionBinding* Binding;

	Binding = &PlayerInputComponent->BindAction(FName("InteractionStart"), IE_Pressed, this, &ASpiderCharacter::StartInteraction);
	Binding = &PlayerInputComponent->BindAction(FName("InteractionCancel"), IE_Pressed, this, &ASpiderCharacter::StopInteraction);

}

void ASpiderCharacter::FellOutOfWorld(const class UDamageType& dmgType)
{
	if (HealthComponent && !HealthComponent->IsDead())
	{
		HealthComponent->SetCurrentHealth(0.0f);
		OnDeath(true);
	}
}

float ASpiderCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("AAbstraction PlayerCharacter:: TakeDamage Damage %.2f"), Damage);
	if (HealthComponent && !HealthComponent->IsDead())
	{
		HealthComponent->TakeDamage(Damage);
		if (HealthComponent->IsDead())
		{
			TogglePostProcess();
			OnDeath(false);
		}
	}

	return Damage;
}

void ASpiderCharacter::OnDeath(bool IsFellOut)
{
	GetWorld()->GetTimerManager().SetTimer(RestartLevelTimerHandle, this, &ASpiderCharacter::OnDeathTimerFinished, TimeRestartLevelAfterDeath, false);
}

void ASpiderCharacter::OnDeathTimerFinished()
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}

void ASpiderCharacter::StartInteraction()
{
	OnInteractionStart.Broadcast();
}

void ASpiderCharacter::StopInteraction()
{
	OnInteractionCancel.Broadcast();
}

const bool ASpiderCharacter::IsAlive() const
{
	if (HealthComponent)
	{
		return !HealthComponent->IsDead();
	}
	return false;
}

const float ASpiderCharacter::GetCurrentHealth() const
{
	if (HealthComponent)
	{
		return HealthComponent->GetCurrentHealth();
	}
	return 0.0f;
}

void ASpiderCharacter::HandleItemCollected()
{
	ItemsCollected++;

	//PC->PlayerCameraManager->PlayCameraShake(CamShake, 1.0f);

	PC->PlayDynamicForceFeedback(ForceFeedBackIntensity, ForceFeedbackDuration, true, false, true, false, EDynamicForceFeedbackAction::Start);

	ItemCollected();
}

void ASpiderCharacter::RequestSprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ASpiderCharacter::RequestSprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

