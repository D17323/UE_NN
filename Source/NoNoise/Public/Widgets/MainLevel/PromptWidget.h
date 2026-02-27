// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PromptWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class NONOISE_API UPromptWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPromptWidget(const FObjectInitializer& OI);
	
	virtual void NativeConstruct() override;
public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PromptText;
	
private:
	UFUNCTION()
	void ChangeText(bool IsTurnRight);
};
