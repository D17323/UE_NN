// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainLevel/TransitionWidget.h"

#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Game/NNPlayerController.h"

UTransitionWidget::UTransitionWidget(const FObjectInitializer& OI):Super(OI)
{
	
}

void UTransitionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (TransitionImage)
	{
		TransitionImage->SetRenderOpacity(1.0f);
		if (ImageFade)
		{
			FWidgetAnimationDynamicEvent Delegate;
			Delegate.BindUFunction(this,"OnFadeFinished");
			BindToAnimationFinished(ImageFade,Delegate);
			PlayAnimation(ImageFade,0,1,EUMGSequencePlayMode::Forward,1);
		}
	}
}

void UTransitionWidget::OnFadeFinished()
{
	ANNPlayerController* NNPC=Cast<ANNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (NNPC && StaminaWidgetClass)
	{
		StaminaWidget=CreateWidget<UStaminaWidget>(NNPC,StaminaWidgetClass);
		StaminaWidget->AddToViewport();
		
		NNPC->StaminaWidget=StaminaWidget;
		NNPC->ResetInputMode(EInputModeCase::ModeGame);
		NNPC->CurrentValue_Severity=0.0f;
		RemoveFromParent();
	}
}
