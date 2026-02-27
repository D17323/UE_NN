// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NNGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NONOISE_API UNNGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	float MainSoundValue=0.5f;
	float BgSoundValue=0.5f;
	float CharacterSoundValue=0.5f;
};
