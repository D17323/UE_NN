// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractActorsBase.h"
#include "InteractActor_Paper.generated.h"

class UGameTextWidget;
/**
 * 
 */
UCLASS()
class NONOISE_API AInteractActor_Paper : public AInteractActorsBase
{
	GENERATED_BODY()
	
protected:
	AInteractActor_Paper();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* Paper;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UGameTextWidget> GameTextWidgetClass;
	
	UPROPERTY(BlueprintReadWrite)
	UGameTextWidget* GameTextWidget;
	
	virtual void Interact() const override;
	virtual void Interact_Implementation() override;
	
public:
	UPROPERTY(BlueprintReadWrite)
	bool bCanInteract=false;
};
