// Fill out your copyright notice in the Description page of Project Settings.


#include "NnAI/Tasks/Patrol.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/NNEnemy.h"
#include "NnAI/NN_AIController.h"

UPatrol::UPatrol()
{
	NodeName = "Patrol";
}

EBTNodeResult::Type UPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANN_AIController* AIC=Cast<ANN_AIController>(OwnerComp.GetAIOwner());
	ANNEnemy* Enemy=Cast<ANNEnemy>(AIC->GetPawn());
	
	if (AIC && !Enemy->PatrolPoints.IsEmpty())
	{
		Index=AIC->GetBlackboard()->GetValueAsInt(PointIndexKey.SelectedKeyName);
		AIC->GetBlackboard()->SetValueAsVector(
			PatrolPointKey.SelectedKeyName,
			Enemy->PatrolPoints[Index]->GetActorLocation()
			);
		if (!bIsBack)
		{
			IndexCalculate_Forward(Index,Enemy->PatrolPoints.Num(),AIC);
		}
		else
		{
			IndexCalculate_Reverse(Index,Enemy->PatrolPoints.Num(),AIC);
		}
		
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}

void UPatrol::IndexCalculate_Forward(int32 PointIndex, int32 Len, ANN_AIController* Controller)
{
	Controller->GetBlackboard()->SetValueAsInt(PointIndexKey.SelectedKeyName,(PointIndex+1)%Len);
	if ((PointIndex+1)%Len==Len-1)
	{
		bIsBack=true;
	}
}
void UPatrol::IndexCalculate_Reverse(int32 PointIndex, int32 Len, ANN_AIController* Controller)
{
	Controller->GetBlackboard()->SetValueAsInt(PointIndexKey.SelectedKeyName,(PointIndex+Len-1)%Len);
	if ((PointIndex+Len-1)%Len==0)
	{
		bIsBack=false;
	}	
}
