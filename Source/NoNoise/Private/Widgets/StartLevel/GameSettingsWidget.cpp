// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StartLevel/GameSettingsWidget.h"

#include "Components/Button.h"
#include "Widgets/Settings/GameAudioSettingsWidget.h"

UGameSettingsWidget::UGameSettingsWidget(const FObjectInitializer& OI):Super(OI)
{
}

void UGameSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Back_btn)
	{
		Back_btn->OnClicked.AddDynamic(this, &UGameSettingsWidget::BackAction);
	}
	if (WidgetMove)
	{
		PlayAnimation(WidgetMove,0,1,EUMGSequencePlayMode::Forward,1);
	}
}


void UGameSettingsWidget::SetVolumeValue(float MainValue, float BgValue, float CharacterValue)
{
	if (GameAudioSettingsWidget)
		GameAudioSettingsWidget->SetAllVolumeValue(MainValue,BgValue,CharacterValue);
}

void UGameSettingsWidget::BackAction()
{
	if (WidgetMove)
	{
		PlayAnimation(WidgetMove,0,1,EUMGSequencePlayMode::Reverse,1);
	}
	if (GameAudioSettingsWidget)
	{
		MainSoundValue=GameAudioSettingsWidget->MainVolumeSliderValue;
		BgSoundValue=GameAudioSettingsWidget->BgVolumeSliderValue;
		CharacterSoundValue=GameAudioSettingsWidget->CharacterVolumeSliderValue;
	}
	
	OnBackPressed.Broadcast();
}
