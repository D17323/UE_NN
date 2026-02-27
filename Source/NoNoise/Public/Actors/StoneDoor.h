// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoneDoor.generated.h"

class UTimelineComponent;
class AInteractActor_Valve;

UCLASS()
class NONOISE_API AStoneDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	AStoneDoor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckPassword(int32 ValveNumber,int32 ValvePassword);
	
	UPROPERTY()
	TArray<int32> Password_door;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTimelineComponent* OpenDoorTL;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UCurveFloat* CF_OpenDoor;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sounds")
	USoundBase* OpenStoneDoorSound;
	
	UPROPERTY()
	FVector StartLocation;
	UPROPERTY()
	FVector EndLocation;
	
	UFUNCTION()
	void OnTimelineUpdate(float output);
	
	UFUNCTION()
	void OnTimelineFinished();
public:	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Password")
	FString StoneDoorPassword;
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Password")
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Valves")
	TArray<AInteractActor_Valve*> ValveActors;
	
	
};
