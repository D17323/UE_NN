// Fill out your copyright notice in the Description page of Project Settings.


#include "NnAI/Tasks/MoveToRandomLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NnAI/NN_AIController.h"

UMoveToRandomLocation::UMoveToRandomLocation()
{
	NodeName = "MoveToRandomLocation";
}

EBTNodeResult::Type UMoveToRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANN_AIController* AIC=Cast<ANN_AIController>(OwnerComp.GetAIOwner());
	if (!AIC) return EBTNodeResult::Failed;
	
	APawn* AIP=AIC->GetPawn();
	if (!AIP) return EBTNodeResult::Failed;
	
	FNavLocation TargetLocation;
	UNavigationSystemV1* NavSys=UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSys)
	{
		bool bIsFound=NavSys->GetRandomPointInNavigableRadius(
			AIP->GetActorLocation(),
			1500.f,
			TargetLocation,
			nullptr
		);
		if (bIsFound)
		{
			AIC->GetBlackboard()->SetValueAsVector(TargetLocationKey.SelectedKeyName,TargetLocation);
			
			FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
