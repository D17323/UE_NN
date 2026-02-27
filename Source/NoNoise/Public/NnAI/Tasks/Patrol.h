// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NnAI/NN_AIController.h"
#include "Patrol.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NONOISE_API UPatrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	UPatrol();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, Category=TargetKey)
	FBlackboardKeySelector PatrolPointKey;
	UPROPERTY(EditAnywhere, Category=TargetKey)
	FBlackboardKeySelector PointIndexKey;
	
	UPROPERTY()
	int32 Index;
	
	UPROPERTY()
	bool bIsBack=false;
	
	UFUNCTION()
	void IndexCalculate_Forward(int32 PointIndex, int32 Len, ANN_AIController* Controller);
	UFUNCTION()
	void IndexCalculate_Reverse(int32 PointIndex, int32 Len, ANN_AIController* Controller);
};
