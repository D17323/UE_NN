// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Settings/GameAudioSettingsWidget.h"

#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"

UGameAudioSettingsWidget::UGameAudioSettingsWidget(const FObjectInitializer& OI):Super(OI)
{
}

void UGameAudioSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (MainVolumeSlider)
	{
		MainVolumeSlider->OnValueChanged.AddDynamic(this,&UGameAudioSettingsWidget::ChangeMainVolumeSlider);
	}
	if (BgVolumeSlider)
	{
		BgVolumeSlider->OnValueChanged.AddDynamic(this,&UGameAudioSettingsWidget::ChangeBgVolumeSlider);
	}
	if (CharacterVolumeSlider)
	{
		CharacterVolumeSlider->OnValueChanged.AddDynamic(this,&UGameAudioSettingsWidget::ChangeCharacterVolumeSlider);
	}
	if (GameSoundMix && BgSoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(MainVolumeSlider,GameSoundMix,MainSoundClass,0.5f,1,0.1);
		UGameplayStatics::SetSoundMixClassOverride(MainVolumeSlider,GameSoundMix,BgSoundClass,0.5f,1,0.1);
		UGameplayStatics::SetSoundMixClassOverride(MainVolumeSlider,GameSoundMix,CharacterSoundClass,0.5f,1,0.1);
	}
}

void UGameAudioSettingsWidget::ChangeMainVolumeSlider(float Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			1.0f,
			FColor::Yellow,
			FString::Printf(TEXT("Value:%2f"),Value));
	}
	if (GameSoundMix && MainSoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(MainVolumeSlider,GameSoundMix,MainSoundClass,Value,1,0.1);
	}
	MainVolumeSliderValue=Value;
}

void UGameAudioSettingsWidget::ChangeBgVolumeSlider(float Value)
{
	if (GameSoundMix && BgSoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(MainVolumeSlider,GameSoundMix,BgSoundClass,Value,1,0.1);
	}
	BgVolumeSliderValue=Value;
}

void UGameAudioSettingsWidget::ChangeCharacterVolumeSlider(float Value)
{
	if (GameSoundMix && CharacterSoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(MainVolumeSlider,GameSoundMix,CharacterSoundClass,Value,1,0.1);
	}
	CharacterVolumeSliderValue=Value;
}

void UGameAudioSettingsWidget::SetAllVolumeValue(float MainValue, float BgValue, float CharacterValue)
{
	MainVolumeSlider->SetValue(MainValue);
	BgVolumeSlider->SetValue(BgValue);
	CharacterVolumeSlider->SetValue(CharacterValue);
	if (GameSoundMix && BgSoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(MainVolumeSlider,GameSoundMix,MainSoundClass,MainValue,1,0.1);
		UGameplayStatics::SetSoundMixClassOverride(MainVolumeSlider,GameSoundMix,BgSoundClass,BgValue,1,0.1);
		UGameplayStatics::SetSoundMixClassOverride(MainVolumeSlider,GameSoundMix,CharacterSoundClass,CharacterValue,1,0.1);
	}
}
