// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "StartLevelWidget.generated.h"

class UNNGameInstance;
class ANNPlayerController;
class UGameSettingsWidget;
class UButton;
/**
 * 
 */
UCLASS()
class NONOISE_API UStartLevelWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UStartLevelWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;
	
	FTimerHandle FadeTimer;
	FWidgetAnimationDynamicEvent BtnMoveDelegate;
	
public:
	UPROPERTY(meta=(BindWidget))
	UButton* GameStart_btn;
	
	UPROPERTY(meta=(BindWidget))
	UButton* GameSettings_btn;
	
	UPROPERTY(meta=(BindWidget))
	UButton* GameQuit_btn;
	
	UPROPERTY(meta=(BindWidget))
	UImage* TransitionImage;
	
	UPROPERTY(BlueprintReadOnly,Transient,meta=(BindWidgetAnim))
	UWidgetAnimation* ImageFade;
	UPROPERTY(BlueprintReadOnly,Transient,meta=(BindWidgetAnim))
	UWidgetAnimation* BtnMove;
	UPROPERTY(BlueprintReadOnly,Transient,meta=(BindWidgetAnim))
	UWidgetAnimation* BtnFade;
	
	UPROPERTY()
	ANNPlayerController* NNPC;
	
	UPROPERTY()
	UNNGameInstance* NNGI;
private:
	UFUNCTION()
	void OnGameStart();
	
	UFUNCTION()
	void OnGameSettings();
	
	UFUNCTION()
	void OnGameQuit();
	
	UFUNCTION()
	void OnFadeFinished();
	
	UFUNCTION()
	void WidgetReverse();
	UFUNCTION()
	void WidgetReverseFinished();

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GameSettings",meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameSettingsWidget> GameSettingsWidgetClass;
	
	UPROPERTY(BlueprintReadOnly,Category="GameSettings",meta=(AllowPrivateAccess=true))
	UGameSettingsWidget* GameSettingsWidget;
};
