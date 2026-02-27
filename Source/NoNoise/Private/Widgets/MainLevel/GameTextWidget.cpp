// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainLevel/GameTextWidget.h"

#include "Components/Button.h"
#include "Game/NNPlayerController.h"
#include "Kismet/GameplayStatics.h"

UGameTextWidget::UGameTextWidget(const FObjectInitializer& OI):Super(OI)
{
}

void UGameTextWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (closebtn)
	{
		closebtn->OnClicked.AddDynamic(this,&UGameTextWidget::CloseWidget);
	}
}

void UGameTextWidget::CloseWidget()
{
	RemoveFromParent();
	ANNPlayerController* NNPC=Cast<ANNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (NNPC)
	{
		NNPC->ResetInputMode(EInputModeCase::ModeGame);
	}
}
