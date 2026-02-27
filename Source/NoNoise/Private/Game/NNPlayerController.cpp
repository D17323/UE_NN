// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NNPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Actors/InteractActor_Valve.h"
#include "Characters/NNPlayer.h"
#include "Components/SpotLightComponent.h"
#include "Game/NN_HUD.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widgets/MainLevel/GamePasueWidget.h"
#include "Widgets/MainLevel/StaminaWidget.h"

ANNPlayerController::ANNPlayerController()
{
}

void ANNPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	NnPlayer=Cast<ANNPlayer>(GetPawn());
	GameHud=Cast<ANN_HUD>(GetHUD());
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultInputMappingContext,0);
	}
	
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			SeverityTimer,
			this,
			&ANNPlayerController::SeverityIncrease,
			0.1f,
			true,
			0.0f
		);
	}
}

void ANNPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent=Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ANNPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ANNPlayerController::Look);
		EnhancedInputComponent->BindAction(UseMedicineAction,ETriggerEvent::Started,this,&ANNPlayerController::UseMedicine);
		EnhancedInputComponent->BindAction(SprintAction,ETriggerEvent::Started,this,&ANNPlayerController::Sprint);
		EnhancedInputComponent->BindAction(SprintAction,ETriggerEvent::Completed,this,&ANNPlayerController::StopSprint);
		EnhancedInputComponent->BindAction(InteractAction,ETriggerEvent::Started,this,&ANNPlayerController::Interact);
		EnhancedInputComponent->BindAction(QuitAction,ETriggerEvent::Started,this,&ANNPlayerController::Quit);
		EnhancedInputComponent->BindAction(LightAction,ETriggerEvent::Started,this,&ANNPlayerController::Light);
		EnhancedInputComponent->BindAction(SwitchValveRotationAction,ETriggerEvent::Started,this,&ANNPlayerController::SwitchValveRotationState);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("No enhanced input component found!"));
	}
}

void ANNPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector=Value.Get<FVector2D>();
	
	const FRotator Rotation=GetControlRotation();
	const FRotator YawRotation(0,Rotation.Yaw,0);
	
	const FVector ForwardVector=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	GetPawn()->AddMovementInput(ForwardVector, MoveVector.Y);
	GetPawn()->AddMovementInput(RightVector, MoveVector.X);
	
	
}

void ANNPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookVector=Value.Get<FVector2D>();
	
	GetPawn()->AddControllerYawInput(LookVector.X);
	GetPawn()->AddControllerPitchInput(LookVector.Y);
}


void ANNPlayerController::UseMedicine()
{
	if (GameHud)
	{
		if (LastUseTime==0.0f)
		{
			SeverityDecrease();
			LastUseTime=GetWorld()->GetTimeSeconds();
		}
		else if (UseMedicineCD()>=5.0f)
		{
			SeverityDecrease();
			LastUseTime=CurrentUseTime;
		}
	}
}

void ANNPlayerController::Sprint()
{
	bCanSprint=true;
	GetWorld()->GetTimerManager().ClearTimer(StopSprintTimer);
	GetWorld()->GetTimerManager().ClearTimer(StaminaRecoverTimer);
	NnPlayer->GetCharacterMovement()->MaxWalkSpeed=700.0f;
	if (CurrentStamina>=MinStamina)
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(
				StartSprintTimer,
				[this]()
				{
					CurrentStamina=FMath::Clamp(CurrentStamina-(1.5+CurrentValue_Severity/100.f),MinStamina,MaxStamina);
					if (CurrentStamina<=MinStamina)
					{
						NnPlayer->GetCharacterMovement()->MaxWalkSpeed=400.0f;
						StaminaRecover();
					}
				},
				0.1f,
				true
			);
		}
		
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(StartSprintTimer);
	}
}

void ANNPlayerController::StopSprint()
{
	GetWorld()->GetTimerManager().ClearTimer(StartSprintTimer);
	GetWorld()->GetTimerManager().ClearTimer(StaminaRecoverTimer);
	NnPlayer->GetCharacterMovement()->MaxWalkSpeed=400.0f;
	if (CurrentStamina<=MaxStamina)
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(
				StopSprintTimer,
				[this]()
				{
					if (GameHud)
					{
						CurrentStamina=CurrentStamina+(1-CurrentValue_Severity/100.0f);
						CurrentStamina=FMath::Clamp(CurrentStamina,MinStamina,MaxStamina);
					}
				},
				0.1f,
				true
			);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(StopSprintTimer);
	}
}

void ANNPlayerController::Interact()
{
	if (NnPlayer)
		NnPlayer->OnInteract();
}

void ANNPlayerController::Quit()
{
	if (GamePasueWidgetClass && !GamePasueWidget)
	{
		GamePasueWidget=CreateWidget<UGamePasueWidget>(this,GamePasueWidgetClass);
		GamePasueWidget->AddToViewport();
		ResetInputMode(EInputModeCase::ModeUI);
	}
	else
	{
		GamePasueWidget->RemoveFromParent();
		GamePasueWidget=nullptr;
		ResetInputMode(EInputModeCase::ModeGame);
	}
}

void ANNPlayerController::Light()
{
	if (IsLightON)
	{
		NnPlayer->FlashLight->SetVisibility(false);
		IsLightON=false;
	}
	else
	{
		NnPlayer->FlashLight->SetVisibility(true);
		IsLightON=true;
	}
}

void ANNPlayerController::SwitchValveRotationState()
{
	
	if (InteractActor_ValveRef)
	{
		if (bTurnRight)
		{
			InteractActor_ValveRef->IsTurnRight=false;
			bTurnRight=false;
			OnTabPressed.Broadcast(bTurnRight);
		}
		else
		{
			InteractActor_ValveRef->IsTurnRight=true;
			bTurnRight=true;
			OnTabPressed.Broadcast(bTurnRight);
		}
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
			-1,
			2.f,
			FColor::Green,
			FString::Printf(TEXT("Tab"))
			);
		}
	}
}

void ANNPlayerController::StaminaRecover()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(StartSprintTimer);
		GetWorld()->GetTimerManager().SetTimer(
			StaminaRecoverTimer,
			[this]()
			{
				CurrentStamina=FMath::Clamp(CurrentStamina+(1-CurrentValue_Severity/100.0f),MinStamina,MaxStamina);
				if (CurrentStamina>=20.0f)
					Sprint();
			},
			0.1f,
			true
		);
	}
}

float ANNPlayerController::UseMedicineCD()
{
	CurrentUseTime=GetWorld()->GetTimeSeconds();
	
	return CurrentUseTime-LastUseTime;
}

void ANNPlayerController::SeverityIncrease()
{
	if (CurrentValue_Severity<100.0f)
	{
		CurrentValue_Severity=CurrentValue_Severity+UKismetMathLibrary::MapRangeClamped(1-CurrentStamina/100.0f,0,1,0.3,0.6);
		CurrentValue_Severity=FMath::Clamp(CurrentValue_Severity,0.0f,100.0f);
		if (StaminaWidget)
			StaminaWidget->SetSeverityPB(CurrentValue_Severity);
	}
	if (CurrentValue_Severity==100.0f)
	{
		if (SeverityTimer.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(SeverityTimer);
		}
	}
}

void ANNPlayerController::SeverityDecrease()
{
	if (GetWorld())
	{
		if (SeverityTimer.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(SeverityTimer);
		}
		GetWorld()->GetTimerManager().SetTimer(
			SeverityTimer,
			this,
			&ANNPlayerController::SeverityDecreaseCalculate,
			0.1f,
			true,
			0.0f
		);
	}
}

void ANNPlayerController::SeverityDecreaseCalculate()
{
	CurrentValue_Severity=FMath::Clamp(CurrentValue_Severity-1.0f,0.0f,100.0f);
	reduceValue++;
	
	if (StaminaWidget)
		StaminaWidget->SetSeverityPB(CurrentValue_Severity);
	
	if (reduceValue==75.0f || CurrentValue_Severity==0.0f)
	{
		if (SeverityTimer.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(SeverityTimer);
		}
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(
				SeverityTimer,
				this,
				&ANNPlayerController::SeverityIncrease,
				0.1f,
				true,
				0.0f
			);
		}
		reduceValue=0.0f;
	}
}

void ANNPlayerController::ResetInputMode(EInputModeCase InputModeCase)
{
	if (InputModeCase==EInputModeCase::ModeUI)
	{
		FInputModeUIOnly InputModeUI;
		InputModeUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputModeUI);
		bShowMouseCursor=true;
	}
	else if (InputModeCase==EInputModeCase::ModeGame)
	{
		FInputModeGameOnly InputModeGame;
		SetInputMode(InputModeGame);
		bShowMouseCursor=false;
	}
	else if (InputModeCase==EInputModeCase::ModeGameUI)
	{
		FInputModeGameAndUI InputModeGameUI;
		SetInputMode(InputModeGameUI);
		bShowMouseCursor=false;
	}
}
