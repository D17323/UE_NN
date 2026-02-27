// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractActor_Paper.h"

#include "Game/NNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/MainLevel/GameTextWidget.h"

AInteractActor_Paper::AInteractActor_Paper()
{
	SceneComponent=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	Paper=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paper"));
	Paper->SetupAttachment(RootComponent);
	
	
}

void AInteractActor_Paper::Interact() const
{
	Super::Interact();
}

void AInteractActor_Paper::Interact_Implementation()
{
	Super::Interact_Implementation();
	if (bCanInteract)
	{
		if (GameTextWidgetClass)
		{
			ANNPlayerController* NNPC=Cast<ANNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
			GameTextWidget=CreateWidget<UGameTextWidget>(NNPC,GameTextWidgetClass);
			GameTextWidget->AddToViewport();
			NNPC->ResetInputMode(EInputModeCase::ModeUI);
		}
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
			-1,
			2.f,
			FColor::Green,
			FString::Printf(TEXT("This is Paper"))
			);
		}
	}
	
}
