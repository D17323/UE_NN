// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StartLevel/StartLevelWidget.h"

#include "Components/Button.h"
#include "Game/NNGameInstance.h"
#include "Game/NNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/StartLevel/GameSettingsWidget.h"


UStartLevelWidget::UStartLevelWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void UStartLevelWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (GameStart_btn)
	{
		GameStart_btn->OnClicked.AddDynamic(this,&UStartLevelWidget::OnGameStart);
	}
	if (GameSettings_btn)
	{
		GameSettings_btn->OnClicked.AddDynamic(this,&UStartLevelWidget::OnGameSettings);
	}
	if (GameQuit_btn)
	{
		GameQuit_btn->OnClicked.AddDynamic(this,&UStartLevelWidget::OnGameQuit);
	}
	if (TransitionImage)
	{
		TransitionImage->SetRenderOpacity(0.0f);
	}
}

void UStartLevelWidget::OnGameStart()
{

	if (BtnFade)
	{
		PlayAnimation(BtnFade,0,1,EUMGSequencePlayMode::Forward,1);
	}
	if (ImageFade)
	{
		FWidgetAnimationDynamicEvent Delegate;
		Delegate.BindUFunction(this,"OnFadeFinished");
		BindToAnimationFinished(
			ImageFade,
			Delegate
		);
		PlayAnimation(ImageFade,0,1,EUMGSequencePlayMode::Forward,1);
	}
	
}

void UStartLevelWidget::OnGameSettings()
{
	if (BtnMove)
	{
		BtnMoveDelegate.Clear();
		UnbindAllFromAnimationFinished(BtnMove);
		PlayAnimation(BtnMove,0,1,EUMGSequencePlayMode::Forward,1);
	}
	NNPC=Cast<ANNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	NNGI=Cast<UNNGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameSettingsWidgetClass)
	{
		GameSettingsWidget=CreateWidget<UGameSettingsWidget>(NNPC,GameSettingsWidgetClass);
		GameSettingsWidget->AddToViewport();
		NNPC->ResetInputMode(EInputModeCase::ModeUI);
		GameSettingsWidget->OnBackPressed.AddDynamic(this,&UStartLevelWidget::WidgetReverse);
		GameSettingsWidget->SetVolumeValue(NNGI->MainSoundValue,NNGI->BgSoundValue,NNGI->CharacterSoundValue);
	}
}

void UStartLevelWidget::OnGameQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),nullptr,EQuitPreference::Quit,false);
}

void UStartLevelWidget::OnFadeFinished()
{
	UGameplayStatics::OpenLevel(GetWorld(),"MainLevel");
}

void UStartLevelWidget::WidgetReverse()
{
	if (BtnMove)
	{
		NNGI->MainSoundValue=GameSettingsWidget->MainSoundValue;
		NNGI->BgSoundValue=GameSettingsWidget->BgSoundValue;
		NNGI->CharacterSoundValue=GameSettingsWidget->CharacterSoundValue;
		
		BtnMoveDelegate.BindUFunction(this,FName("WidgetReverseFinished"));
		BindToAnimationFinished(BtnMove,BtnMoveDelegate);
		PlayAnimation(BtnMove,0,1,EUMGSequencePlayMode::Reverse,1);
	}
}

void UStartLevelWidget::WidgetReverseFinished()
{
	if (GameSettingsWidget)
	{
		GameSettingsWidget->OnBackPressed.Clear();
		GameSettingsWidget->RemoveFromParent();
	}
}

