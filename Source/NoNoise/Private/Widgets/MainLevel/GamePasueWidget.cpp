// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainLevel/GamePasueWidget.h"

#include "Game/NNGameInstance.h"
#include "Game/NNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/StartLevel/GameSettingsWidget.h"

UGamePasueWidget::UGamePasueWidget(const FObjectInitializer& OI):Super(OI)
{
}

void UGamePasueWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (GameContinue_btn)
	{
		GameContinue_btn->OnClicked.AddDynamic(this, &UGamePasueWidget::GameContinue);
	}
	if (GameSettings_btn)
	{
		GameSettings_btn->OnClicked.AddDynamic(this, &UGamePasueWidget::GameSettings);
	}
	if (GameQuit_btn)
	{
		GameQuit_btn->OnClicked.AddDynamic(this, &UGamePasueWidget::GameQuit);
	}
}

void UGamePasueWidget::GameContinue()
{
	UGameplayStatics::SetGamePaused(GetWorld(),false);
	RemoveFromParent();
	
	NNPC=Cast<ANNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	NNPC->ResetInputMode(EInputModeCase::ModeGame);
	NNPC->GamePasueWidget=nullptr;
	
}

void UGamePasueWidget::GameQuit()
{
	UGameplayStatics::SetGamePaused(GetWorld(),true);
	UKismetSystemLibrary::QuitGame(GetWorld(),nullptr,EQuitPreference::Quit,false);
}

void UGamePasueWidget::GameSettings()
{
	if (BtnMove)
	{
		Delegate.Clear();
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
		GameSettingsWidget->OnBackPressed.AddDynamic(this,&UGamePasueWidget::WidgetReverse);
		GameSettingsWidget->SetVolumeValue(NNGI->MainSoundValue,NNGI->BgSoundValue,NNGI->CharacterSoundValue);
		
	}
}

void UGamePasueWidget::WidgetReverse()
{
	if (BtnMove)
	{
		NNGI->MainSoundValue=GameSettingsWidget->MainSoundValue;
		NNGI->BgSoundValue=GameSettingsWidget->BgSoundValue;
		NNGI->CharacterSoundValue=GameSettingsWidget->CharacterSoundValue;
		
		Delegate.BindUFunction(this,FName("WidgetReverseFinished"));
		BindToAnimationFinished(BtnMove,Delegate);
		PlayAnimation(BtnMove,0,1,EUMGSequencePlayMode::Reverse,1);
	}
	
}

void UGamePasueWidget::WidgetReverseFinished()
{
	if (GameSettingsWidget)
	{
		GameSettingsWidget->OnBackPressed.Clear();
		GameSettingsWidget->RemoveFromParent();
	}
}
