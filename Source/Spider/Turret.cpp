//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Turret.h"
//#include "SpiderCharacter.h"
//#include "Kismet/GameplayStatics.h"
//#include "TimerManager.h"
//
//void ATurret::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	if (InFireRange() && Character)
//	{
//		RotateTurret(Character->GetActorLocation());
//	}
//}
//
//void ATurret::HandleDestruction()
//{
//	Super::HandleDestruction();
//	Destroy();
//}
//
//void ATurret::BeginPlay()
//{
//	Super::BeginPlay();
//
//	Character = Cast<ASpiderCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
//
//	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
//}
//
//void ATurret::CheckFireCondition()
//{
//	if (InFireRange())
//	{
//		Fire(); // Add debug sphere or actual firing logic here
//	}
//}
//
//bool ATurret::InFireRange()
//{
//	if (Character)
//	{
//		float DistanceBetween = FVector::Dist(Character->GetActorLocation(), GetActorLocation());
//		return DistanceBetween <= FireRange;
//	}
//	return false;
//}