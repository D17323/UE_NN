// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NNCharacterBase.h"
#include "NNPlayer.generated.h"

class USpotLightComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class NONOISE_API ANNPlayer : public ANNCharacterBase
{
	GENERATED_BODY()
	
protected:
	ANNPlayer();
	
public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerCamera")
	UCameraComponent* PlayerCamera;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Audio")
	UAudioComponent* PlayerAudio;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="FlashLight")
	USpotLightComponent* FlashLight;
	
	UFUNCTION()
	void OnInteract();
	
};
