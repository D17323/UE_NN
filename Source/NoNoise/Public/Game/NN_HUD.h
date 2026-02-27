// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NN_HUD.generated.h"

class ANNPlayerController;
class UStaminaWidget;
class UStartLevelWidget;
class UTransitionWidget;
/**
 * 
 */
UCLASS()
class NONOISE_API ANN_HUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Widgets,meta=(AllowPrivateAccess="true"))
	TSubclassOf<UStartLevelWidget> StartLevelWidgetClass;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Widgets,meta=(AllowPrivateAccess="true"))
	TSubclassOf<UTransitionWidget> TransitionWidgetClass;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Widgets,meta=(AllowPrivateAccess="true"))
	TSubclassOf<UStaminaWidget> StaminaWidgetClass;
public:
	
	UPROPERTY()
	UStartLevelWidget* StartLevelWidget;
	
	UPROPERTY()
	UStaminaWidget* StaminaWidget;
	
	UPROPERTY()
	UTransitionWidget* TransitionWidget;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=WidgetDebug)
	bool UseWidgetDebug;
};
