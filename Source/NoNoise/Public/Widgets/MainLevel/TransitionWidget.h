// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaminaWidget.h"
#include "Blueprint/UserWidget.h"
#include "TransitionWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class NONOISE_API UTransitionWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UTransitionWidget(const FObjectInitializer& OI);
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(meta=(BindWidget))
	UImage* TransitionImage;
	
	UPROPERTY(BlueprintReadOnly,Transient,meta=(BindWidgetAnim))
	UWidgetAnimation* ImageFade;
	
	UPROPERTY(BlueprintReadOnly)
	UStaminaWidget* StaminaWidget;
	
private:
	UFUNCTION()
	void OnFadeFinished();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Widgets,meta=(AllowPrivateAccess="true"))
	TSubclassOf<UStaminaWidget> StaminaWidgetClass;
};
