// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameTextWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class NONOISE_API UGameTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UGameTextWidget(const FObjectInitializer& OI);
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UButton* closebtn;
	
	UFUNCTION()
	void CloseWidget();
};
