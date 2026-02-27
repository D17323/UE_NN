// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GamePasueWidget.generated.h"

class UGameSettingsWidget;
class ANNPlayerController;
class UNNGameInstance;
/**
 * 
 */
UCLASS()
class NONOISE_API UGamePasueWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UGamePasueWidget(const FObjectInitializer& OI);
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly,Transient,meta=(BindWidgetAnim))
	UWidgetAnimation* BtnMove;
	
	UPROPERTY()
	FWidgetAnimationDynamicEvent Delegate;
	
	UPROPERTY()
	ANNPlayerController* NNPC;
	
	UPROPERTY()
	UNNGameInstance* NNGI;
private:
	UPROPERTY(meta=(BindWidget))
	UButton* GameContinue_btn;
	
	UPROPERTY(meta=(BindWidget))
	UButton* GameQuit_btn;
	
	UPROPERTY(meta=(BindWidget))
	UButton* GameSettings_btn;
	
	UFUNCTION()
	void GameContinue();
	UFUNCTION()
	void GameQuit();
	UFUNCTION()
	void GameSettings();
	
	UFUNCTION()
	void WidgetReverse();
	UFUNCTION()
	void WidgetReverseFinished();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GameSettings",meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameSettingsWidget> GameSettingsWidgetClass;
	UPROPERTY(BlueprintReadOnly,Category="GameSettings",meta=(AllowPrivateAccess=true))
	UGameSettingsWidget* GameSettingsWidget;
};
