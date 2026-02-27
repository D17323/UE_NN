// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "InteractActorsBase.generated.h"

UCLASS()
class NONOISE_API AInteractActorsBase : public AActor,public IInteractInterface
{
	GENERATED_BODY()
public:
	virtual void Interact() const override;
	
	virtual void Interact_Implementation() override;

};
