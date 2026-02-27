// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Touch.h"
#include "NN_AIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Hearing;
/**
 * 
 */
UCLASS()
class NONOISE_API ANN_AIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	ANN_AIController();
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="BehaviorTree",meta=(AllowPrivateAccess="true"))
	UBehaviorTree* BehaviorTree;
		
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="BehaviorTree",meta=(AllowPrivateAccess="true"))
	UBlackboardComponent* BlackboardComp;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="AIPerception",meta=(AllowPrivateAccess="true"))
	UAIPerceptionComponent* PerceptionComp;
	
	UPROPERTY()
	UAISenseConfig_Sight* Sight_Config;
	
	UPROPERTY()
	UAISenseConfig_Hearing* Hearing_Config;
	
	UPROPERTY()
	UAISenseConfig_Touch* Touch_Config;
	
protected:
	UFUNCTION()
	void SetupPerceptionSystem();
	
	UFUNCTION()
	void UpdateTargetBySense(AActor* Actor,FAIStimulus Stimulus);
	
	UFUNCTION()
	void SetSightConfig();
	
	UFUNCTION()
	void SetHearingConfig();
	
	UFUNCTION()
	void SetTouchConfig();
	
	UFUNCTION()
	void UpdateSightSense(AActor* Actor,FAIStimulus Stimulus);
	
	UFUNCTION()
	void UpdateHearingSense(AActor* Actor,FAIStimulus Stimulus);
	
	UFUNCTION()
	void UpdateTouchSense(AActor* Actor,FAIStimulus Stimulus);
	
public:
	FORCEINLINE UBlackboardComponent* GetBlackboard() const { return Blackboard; }
};
