// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainLevel/PromptWidget.h"

#include "Components/TextBlock.h"
#include "Game/NNPlayerController.h"
#include "Kismet/GameplayStatics.h"

UPromptWidget::UPromptWidget(const FObjectInitializer& OI):Super(OI)
{
}

void UPromptWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ANNPlayerController* NNPC=Cast<ANNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (NNPC)
	{
		NNPC->OnTabPressed.AddDynamic(this,&UPromptWidget::ChangeText);
		/*if (NNPC->bTurnRight)
		{
			PromptText->SetText(FText::FromString("TurnRight"));
		}
		else
		{
			PromptText->SetText(FText::FromString("TurnLeft"));
		}*/
	}
		
}

void UPromptWidget::ChangeText(bool IsTurnRight)
{
	if (IsTurnRight)
	{
		PromptText->SetText(FText::FromString("TurnRight"));
	}
	else
	{
		PromptText->SetText(FText::FromString("TurnLeft"));
	}
}
