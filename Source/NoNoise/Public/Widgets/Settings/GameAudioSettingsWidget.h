// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameAudioSettingsWidget.generated.h"

class USlider;
/**
 * 
 */

UCLASS()
class NONOISE_API UGameAudioSettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UGameAudioSettingsWidget(const FObjectInitializer& OI);
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	USlider* MainVolumeSlider;
	
	UPROPERTY(meta=(BindWidget))
	USlider* BgVolumeSlider;
	
	UPROPERTY(meta=(BindWidget))
	USlider* CharacterVolumeSlider;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=AudioSettings)
	USoundMix* GameSoundMix;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=AudioSettings)
	USoundClass* MainSoundClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=AudioSettings)
	USoundClass* BgSoundClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=AudioSettings)
	USoundClass* CharacterSoundClass;
	
private:
	UFUNCTION()
	void ChangeMainVolumeSlider(float Value);
	
	UFUNCTION()
	void ChangeBgVolumeSlider(float Value);
	
	UFUNCTION()
	void ChangeCharacterVolumeSlider(float Value);
	
public:
	float MainVolumeSliderValue=0.5f;
	float BgVolumeSliderValue=0.5f;
	float CharacterVolumeSliderValue=0.5f;
	
	UFUNCTION()
	void SetAllVolumeValue(float MainValue,float BgValue,float CharacterValue);
};
