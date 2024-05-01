// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderPlayerController.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpiderCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

void ASpiderPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ASpiderPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		//Bind Axis

		//Move
		InputComponent->BindAxis(TEXT("MoveForward"), this, &ASpiderPlayerController::RequestMoveForward);
		//InputComponent->BindAxis(TEXT("MoveRight"), this, &ATantrumPlayerController::RequestMoveRight);

		//Look
		InputComponent->BindAxis(TEXT("LookUp"), this, &ASpiderPlayerController::RequestLookUp);
		InputComponent->BindAxis(TEXT("LookRight"), this, &ASpiderPlayerController::RequestLookRight);

		//Turn
		InputComponent->BindAxis(TEXT("Turn"), this, &ASpiderPlayerController::RequestTurn);

		// Mouse Wheel Zoom In / Zoom Out
		InputComponent->BindAxis(TEXT("MouseWheelAxis"), this, &ASpiderPlayerController::HandleCameraZoom);

		//Bind Actions

		//Throw Object
		//InputComponent->BindAction(TEXT("ThrowObject"), IE_Pressed, this, &ASpiderPlayerController::RequestThrowObject);

		// Jump
		InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ASpiderPlayerController::RequestJump);
		InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ASpiderPlayerController::RequestStopJump);

		//Sprint
		InputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ASpiderPlayerController::RequestSprintStart);
		InputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ASpiderPlayerController::RequestSprintEnd);

		//Crouch
		InputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &ASpiderPlayerController::RequestCrouchStart);
		InputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &ASpiderPlayerController::RequestCrouchEnd);
		InputComponent->BindAction(TEXT("ToggleCrouch"), IE_Pressed, this, &ASpiderPlayerController::ToggleCrouch);

		//Bind Right Mouse Button
		//InputComponent->BindAction(TEXT("AlignToController"), IE_Pressed, this, &ASpiderPlayerController::RequestAlignCharacterToController);
		//InputComponent->BindAction(TEXT("AlignToController"), IE_Released, this, &ASpiderPlayerController::RequestStopAligningCharacterToController);

		// Pulling
		//InputComponent->BindAction(TEXT("PullObject"), EInputEvent::IE_Pressed, this, &ASpiderPlayerController::RequestPullObject);
		//InputComponent->BindAction(TEXT("PullObject"), EInputEvent::IE_Released, this, &ASpiderPlayerController::RequestStopPullObject);

	}
}

void ASpiderPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (bIsAligningCharacter)
	//{
	//	AlignCharacterToController();
	//}

}

void ASpiderPlayerController::RequestMoveForward(float AxisValue)
{
	//if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (AxisValue != 0.0f)
	{
		FRotator const ControlSpaceRot = GetControlRotation();
		GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), AxisValue);
	}
}

void ASpiderPlayerController::HandleCameraZoom(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (GetCharacter())
		{
			UCameraComponent* Camera = GetCharacter()->FindComponentByClass<UCameraComponent>();
			if (Camera)
			{
				float NewFOV = FMath::Clamp(Camera->FieldOfView + AxisValue * ZoomRate, MinZoomFOV, MaxZoomFOV);
				Camera->SetFieldOfView(NewFOV);
			}
		}
	}
}

//void ATantrumPlayerController::RequestMoveRight(float AxisValue)
//{
// 	if(!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) {return;}
//	if (AxisValue != 0.0f)
//	{
//		FRotator const ControlSpaceRot = GetControlRotation();
//		GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), AxisValue);
//	}
//}

void ASpiderPlayerController::RequestTurn(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		AddYawInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void ASpiderPlayerController::RequestLookUp(float AxisValue)
{
	if (bIsAligningCharacter && AxisValue != 0.0f)
	{
		AddPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void ASpiderPlayerController::RequestLookRight(float AxisValue)
{
	if (bIsAligningCharacter && AxisValue != 0.0f)
	{
		AddYawInput(AxisValue * BaseLookRightRate * GetWorld()->GetDeltaSeconds());
	}
}

//void ASpiderPlayerController::RequestThrowObject()
//{
	//if (ATantrumCharacterBase* TantrumCharacterBase = Cast<ATantrumCharacterBase>(GetCharacter()))
	//{
		//if (TantrumCharacterBase->CanThrowObject())
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("RequestThrow"));
		//	TantrumCharacterBase->RequestThrowObject();

		//}
		//else
		//{
		//	return;
		//	//TantrumCharacterBase->RequestUseObject();
		//}
	//}
//}

//void ATantrumPlayerController::RequestThrowObject(float AxisValue)
//{
//	if (ATantrumCharacterBase* TantrumCharacterBase = Cast<ATantrumCharacterBase>(GetCharacter()))
//	{
//		if (TantrumCharacterBase->CanThrowObject())
//		{
//			float currentDelta = AxisValue - LastAxis;
//
//			//debug
//			if (CVarDisplayLaunchInputDelta->GetBool())
//			{
//				if (fabs(currentDelta) > 0.0f)
//				{
//					UE_LOG(LogTemp, Warning, TEXT("Axis: %f LastAxis: %f currentDelta: %f"), AxisValue, LastAxis);
//				}
//			}
//			LastAxis = AxisValue;
//			const bool IsFlick = fabs(currentDelta) > FlickThreshold;
//			if (IsFlick)
//			{
//				TantrumCharacterBase->RequestThrowObject();
//			}
//		}
//		else
//		{
//			LastAxis = 0.0f;
//		}
//	}
//}

void ASpiderPlayerController::RequestJump()
{
	//if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (GetCharacter())
	{
		GetCharacter()->Jump();

		//SoundCue Triggers
		//if (JumpSound && GetCharacter()->GetCharacterMovement()->IsMovingOnGround())
		//{
		//	FVector CharacterLocation = GetCharacter()->GetActorLocation();
		//	UGameplayStatics::PlaySoundAtLocation(this, JumpSound, CharacterLocation);
		//}
	}
}

void ASpiderPlayerController::RequestStopJump()
{
	if (GetCharacter()) // allows a jump hold propoerty in editor
	{
		GetCharacter()->StopJumping();
	}
}

// Toggle Crouch and Uncrouch

void ASpiderPlayerController::ToggleCrouch()
{
	if (GetCharacter())
	{
		if (!GetCharacter()->GetCharacterMovement()->IsMovingOnGround())
		{
			return; // avoid clashes with jump function.
		}

		if (GetCharacter()->bIsCrouched)
		{
			GetCharacter()->UnCrouch();
		}
		else
		{
			GetCharacter()->Crouch();
		}
	}
}

void ASpiderPlayerController::RequestCrouchStart()
{
	//if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (!GetCharacter()->GetCharacterMovement()->IsMovingOnGround()) { return; }
	if (GetCharacter())
	{
		GetCharacter()->Crouch();
	}
}

void ASpiderPlayerController::RequestCrouchEnd()
{
	if (GetCharacter())
	{
		GetCharacter()->UnCrouch();
	}
}

void ASpiderPlayerController::RequestSprintStart()
{

	if (ASpiderCharacter* SpiderCharacter = Cast<ASpiderCharacter>(GetCharacter()))
	{
		SpiderCharacter->RequestSprintStart();
	}
}

void ASpiderPlayerController::RequestSprintEnd()
{
	if (ASpiderCharacter* SpiderCharacter = Cast<ASpiderCharacter>(GetCharacter()))
	{
		SpiderCharacter->RequestSprintEnd();
	}
}

//void ASpiderPlayerController::AlignCharacterToController()
//{
//	if (GetCharacter())
//	{
//		FRotator ControllerRot = GetControlRotation();
//		ControllerRot.Pitch = 0;
//		GetCharacter()->SetActorRotation(ControllerRot);
//	}
//}

//void ASpiderPlayerController::RequestAlignCharacterToController()
//{
//	bIsAligningCharacter = true;
//}
//
//void ASpiderPlayerController::RequestStopAligningCharacterToController()
//{
//	bIsAligningCharacter = false;
//}

//void ASpiderPlayerController::RequestPullObject()
//{
//	if (ATantrumCharacterBase* TantrumCharacterBase = Cast<ATantrumCharacterBase>(GetCharacter()))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("RequestPullObject called"));
//		TantrumCharacterBase->RequestPullObject();
//	}
//}
//
//void ASpiderPlayerController::RequestStopPullObject()
//{
//	if (ATantrumCharacterBase* TantrumCharacterBase = Cast<ATantrumCharacterBase>(GetCharacter()))
//	{
//		TantrumCharacterBase->RequestStopPullObject();
//	}
//}