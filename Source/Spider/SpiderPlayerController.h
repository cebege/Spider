// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpiderPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPIDER_API ASpiderPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	bool bIsAligningCharacter;

	// Mouse Properties:

	UPROPERTY(EditAnywhere, Category = "Camera")
		float ZoomRate = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float MinZoomFOV = 60.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float MaxZoomFOV = 200.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupInputComponent() override;

	// Movement:

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MaxWalkSpeed = 400.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float SprintSpeed = 1000.0f;

	//UPROPERTY(EditAnywhere, Category = "Movement")
	//	float TurnSpeed = 450.0f;

	// Look:

	UPROPERTY(EditAnywhere, Category = "Look")
		float BaseLookUpRate = 50.f;

	UPROPERTY(EditAnywhere, Category = "Look")
		float BaseLookRightRate = 50.f;

	UPROPERTY(EditAnywhere, Category = "Look")
		float BaseTurnRate = 50.f;

public:

	virtual void Tick(float DeltaTime) override;

protected:

	//Bind Axis

	//Move
	void RequestMoveForward(float AxisValue);
	//void RequestMoveRight(float AxisValue);

	//Turn
	void RequestTurn(float AxisValue);

	//Look
	void RequestLookUp(float AxisValue);
	void RequestLookRight(float AxisValue);

	//Zoom In and Zoom Out
	void HandleCameraZoom(float AxisValue);

	//void RequestPullObject();
	//void RequestStopPullObject();
	//void RequestThrowObject();

	//void RequestUseObject();

	//Bind Actions

	//Jump
	void RequestJump();
	void RequestStopJump();

	//Sprint
	void RequestSprintStart();
	void RequestSprintEnd();

	//Crouch
	void RequestCrouchStart();
	void RequestCrouchEnd();
	void ToggleCrouch();

	// Bind Right Mouse Button
	//void AlignCharacterToController();
	//void RequestAlignCharacterToController();
	//void RequestStopAligningCharacterToController();


	//UPROPERTY(EditAnywhere, Category = "HUD")
	//	TSubclassOf<class UUserWidget> HUDClass;

	//UPROPERTY()
	//	UUserWidget* HUDWidget;

	/**Sound Cue for Jumping Sound. */

	//UPROPERTY(EditAnywhere, Category = "Sound")
	//	USoundCue* JumpSound = nullptr;

	//used to determine flick of axis
	//float LastDelta = 0.0f;
	//float LastAxis = 0.0f;

	//UPROPERTY(EditAnywhere, Category = "Input")
	//	float FlickThreshold = 0.75f;

};

