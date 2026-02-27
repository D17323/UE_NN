// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game/NNPlayerController.h"
#include "StaminaWidget.generated.h"

class UImage;
class UProgressBar;
/**
 * 
 */
UCLASS()
class NONOISE_API UStaminaWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UStaminaWidget(const FObjectInitializer& OI);
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual  void NativeDestruct() override;
	
public:
	UFUNCTION()
	void SetStaminaPB();
	UFUNCTION()
	void SetSeverityPB(float Value);

private:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* Stamina_pb;
	
	UPROPERTY(meta=(BindWidget))
	UProgressBar* Severity_pb;
	
	FTimerHandle SeverityTimer;
	FTimerHandle FadeTimer;
	
	float StaminaValue;
	float CurrentValue_Severity;
	float reduceValue;
	
	ANNPlayerController* NNPC;
public:
	
	FORCEINLINE UProgressBar* GetSeverity_pb() const { return Severity_pb; }
};
