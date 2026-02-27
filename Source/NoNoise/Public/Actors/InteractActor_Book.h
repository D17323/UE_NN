// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractActorsBase.h"
#include "InteractActor_Book.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class NONOISE_API AInteractActor_Book : public AInteractActorsBase
{
	GENERATED_BODY()
	
	
protected:
	AInteractActor_Book();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* Book;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PromptWidget")
	UWidgetComponent* PromptWidgetComp;
	
	virtual void Interact() const override;
	virtual void Interact_Implementation() override;
	
public:
	UPROPERTY(BlueprintReadWrite)
	bool bIsPicked=false;
};
