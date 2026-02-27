// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "Characters/NNPlayer.h"
#include "GameFramework/PlayerController.h"
#include "NNPlayerController.generated.h"

class AInteractActor_Valve;
class UStaminaWidget;
class UGamePasueWidget;
class UInputAction;
class ANN_HUD;

UENUM(BlueprintType)
enum class EInputModeCase:uint8
{
	ModeUI UMETA(DisplayName="UI Mode"),
	ModeGame UMETA(DisplayName="Game Mode"),
	ModeGameUI UMETA(DisplayName="Game UI Mode"),
};
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTabPressed,bool,IsTurnRight);
UCLASS()
class NONOISE_API ANNPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	ANNPlayerController();
	virtual void BeginPlay() override;
	
public:
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess=true))
	UInputMappingContext* DefaultInputMappingContext;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="InputAction",meta=(AllowPrivateAccess=true))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="InputAction",meta=(AllowPrivateAccess=true))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="InputAction",meta=(AllowPrivateAccess=true))
	UInputAction* UseMedicineAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="InputAction",meta=(AllowPrivateAccess=true))
	UInputAction* SprintAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="InputAction",meta=(AllowPrivateAccess=true))
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="InputAction",meta=(AllowPrivateAccess=true))
	UInputAction* QuitAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="InputAction",meta=(AllowPrivateAccess=true))
	UInputAction* LightAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="InputAction",meta=(AllowPrivateAccess=true))
	UInputAction* SwitchValveRotationAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void UseMedicine();
	void Sprint();
	void StopSprint();
	void Interact();
	void Quit();
	void Light();
	void SwitchValveRotationState();

	FTimerHandle StartSprintTimer;
	FTimerHandle StopSprintTimer;
	FTimerHandle StaminaRecoverTimer;
	FTimerHandle SeverityTimer;
	
	void StaminaRecover();
	float UseMedicineCD();
	void SeverityIncrease();
	void SeverityDecrease();
	void SeverityDecreaseCalculate();
	
	UPROPERTY()
	ANNPlayer* NnPlayer;
	UPROPERTY()
	ANN_HUD* GameHud;
	
	
public:
	UPROPERTY()
	FOnTabPressed OnTabPressed;
	
	UFUNCTION()
	void ResetInputMode(EInputModeCase InputModeCase);
	
	float LastUseTime=0.0f;
	float CurrentUseTime=0.0f;
	
	float MaxStamina=100.0f;
	float CurrentStamina=100.0f;
	float MinStamina=0.0f;
	bool bCanSprint=false;
	
	float CurrentValue_Severity=0.0f;
	float reduceValue=0.0f;
	
	bool IsLightON=false;
	
	UPROPERTY()
	UGamePasueWidget* GamePasueWidget;
	UPROPERTY()
	UStaminaWidget* StaminaWidget;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sounds")
	USoundWave* AsthmaWav;

	UPROPERTY(BlueprintReadWrite)
	AInteractActor_Valve* InteractActor_ValveRef;
	UPROPERTY(BlueprintReadWrite)
	bool bTurnRight;
	
private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Widgets,meta=(AllowPrivateAccess="true"))
	TSubclassOf<UGamePasueWidget> GamePasueWidgetClass;
	
};
