// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NN_HUD.h"

#include "Game/NNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/MainLevel/TransitionWidget.h"
#include "Widgets/StartLevel/StartLevelWidget.h"

void ANN_HUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (TransitionWidgetClass && StartLevelWidgetClass && StaminaWidgetClass)
	{
		ANNPlayerController* AnnPlayerController=Cast<ANNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
		FString CurrentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld());
		if (AnnPlayerController)
		{
			if (CurrentLevel=="StartLevel")
			{
            	StartLevelWidget=CreateWidget<UStartLevelWidget>(AnnPlayerController,StartLevelWidgetClass);
				StartLevelWidget->AddToViewport();
				AnnPlayerController->ResetInputMode(EInputModeCase::ModeUI);
			}
			else
			{
				if (UseWidgetDebug)
				{
					StaminaWidget=CreateWidget<UStaminaWidget>(AnnPlayerController,StaminaWidgetClass);
					StaminaWidget->AddToViewport();
					AnnPlayerController->StaminaWidget=StaminaWidget;
					AnnPlayerController->ResetInputMode(EInputModeCase::ModeGame);
				}
				else
				{
					TransitionWidget=CreateWidget<UTransitionWidget>(AnnPlayerController,TransitionWidgetClass);
					AnnPlayerController->ResetInputMode(EInputModeCase::ModeUI);
					AnnPlayerController->bShowMouseCursor=false;
					TransitionWidget->SetCursor(EMouseCursor::None);
					TransitionWidget->AddToViewport();
				}
				
			}
		}
		
	}
}

