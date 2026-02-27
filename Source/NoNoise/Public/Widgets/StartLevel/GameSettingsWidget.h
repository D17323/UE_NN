// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameSettingsWidget.generated.h"

class UButton;
class UGameAudioSettingsWidget;
class USlider;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackPressed);
UCLASS()
class NONOISE_API UGameSettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UGameSettingsWidget(const FObjectInitializer& OI);
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UGameAudioSettingsWidget* GameAudioSettingsWidget;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Back_btn;
	
	UPROPERTY(BlueprintReadOnly,Transient,meta=(BindWidgetAnim))
	UWidgetAnimation* WidgetMove;
	
public:
	UPROPERTY()
	FOnBackPressed OnBackPressed;
	
	UFUNCTION()
	void SetVolumeValue(float MainValue,float BgValue,float CharacterValue);
	float MainSoundValue;
	float BgSoundValue;
	float CharacterSoundValue;
private:
	UFUNCTION()
	void BackAction();
};
