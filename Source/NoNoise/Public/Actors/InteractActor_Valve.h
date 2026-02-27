// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractActorsBase.h"
#include "InteractActor_Valve.generated.h"


class ANNPlayerController;
class UWidgetComponent;
class UBoxComponent;
class UTimelineComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnValveStateChanged, int32, ValveNumber, int32, ValvePassword);

UCLASS()
class NONOISE_API AInteractActor_Valve : public AInteractActorsBase
{
	GENERATED_BODY()
	
protected:
	AInteractActor_Valve();
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Number")
	int32 ValveNumber=0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Number")
	int32 ValvePassword;
	
	UPROPERTY(BlueprintAssignable)
	FOnValveStateChanged OnValveStateChanged;
	
	UFUNCTION(BlueprintCallable)
	void ChangeValve();

	UPROPERTY()
	UTimelineComponent* TimelineComp;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Curve")
	UCurveFloat* CF_Valve;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsTurnRight=false;
	
	UPROPERTY(BlueprintReadOnly)
	ANNPlayerController* NNPC;
private:
	UFUNCTION()
	void OnTimelineUpdate(float output);
	
	UFUNCTION()
	void OnTimelineFinished();
	
	UFUNCTION()
	void OnBoxTriggerBegin(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult & SweepResult);
	
	UFUNCTION()
	void OnBoxTriggerEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
	
	UFUNCTION()
	void ChangeValveState(bool bIsTurnRight);
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UBoxComponent* TriggerBox;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* Valve;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PromptWidget")
	UWidgetComponent* PromptWidgetComp;
	
	FRotator CurrentRotation;
	FRotator NextRotation;
	FRotator NewRotation;
	float StartValue;
	float EndValue;
	
	bool CanUseValve=false;
	
	virtual void Interact() const override;
	virtual void Interact_Implementation() override;
};
