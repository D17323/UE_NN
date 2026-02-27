// Fill out your copyright notice in the Description page of Project Settings.


#include "NnAI/NN_AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISense_Touch.h"

ANN_AIController::ANN_AIController()
{
	BlackboardComp=CreateDefaultSubobject<UBlackboardComponent>("BlackboardComp");
	PerceptionComp=CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	
	SetupPerceptionSystem();
}

void ANN_AIController::BeginPlay()
{
	Super::BeginPlay();
	if (PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ANN_AIController::UpdateTargetBySense);
	}
	if (BehaviorTree != nullptr)
		RunBehaviorTree(BehaviorTree);
}

void ANN_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (BlackboardComp && BehaviorTree->BlackboardAsset)
	{
		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		GetBlackboard()->SetValueAsBool("SeePlayer", false);
		GetBlackboard()->SetValueAsBool("IsHearingSomething", false);
		GetBlackboard()->SetValueAsEnum("EAIAction",0);
		GetBlackboard()->SetValueAsInt("PatrolPointIndex",0);
	}
}

void ANN_AIController::SetupPerceptionSystem()
{
	SetSightConfig();
	SetHearingConfig();
	SetTouchConfig();
}

void ANN_AIController::UpdateTargetBySense(AActor* Actor, FAIStimulus Stimulus)
{
	UpdateSightSense(Actor,Stimulus);
	UpdateHearingSense(Actor, Stimulus);
	UpdateTouchSense(Actor, Stimulus);
}

void ANN_AIController::SetSightConfig()
{
	Sight_Config=CreateDefaultSubobject<UAISenseConfig_Sight>("Sight_Config");
	if (Sight_Config)
	{
		Sight_Config->SightRadius=500.0f;
		Sight_Config->LoseSightRadius=Sight_Config->SightRadius+50.0f;
		Sight_Config->PeripheralVisionAngleDegrees=50.0f;
		Sight_Config->AutoSuccessRangeFromLastSeenLocation=50.0f;
		
		Sight_Config->DetectionByAffiliation.bDetectEnemies=true;
		Sight_Config->DetectionByAffiliation.bDetectFriendlies=true;
		Sight_Config->DetectionByAffiliation.bDetectNeutrals=true;
		
		PerceptionComp->SetDominantSense(Sight_Config->GetSenseImplementation());
		PerceptionComp->ConfigureSense(*Sight_Config);
	}
}

void ANN_AIController::SetHearingConfig()
{
	Hearing_Config=CreateDefaultSubobject<UAISenseConfig_Hearing>("HearingConfig");
	if (Hearing_Config)
	{
		Hearing_Config->HearingRange=3000.0f;
		Hearing_Config->DetectionByAffiliation.bDetectEnemies=true;
		Hearing_Config->DetectionByAffiliation.bDetectFriendlies=true;
		Hearing_Config->DetectionByAffiliation.bDetectNeutrals=true;
		
		PerceptionComp->ConfigureSense(*Hearing_Config);
	}
}

void ANN_AIController::SetTouchConfig()
{
	Touch_Config=CreateDefaultSubobject<UAISenseConfig_Touch>("TouchConfig");
	if (Touch_Config)
	{
		PerceptionComp->ConfigureSense(*Touch_Config);
	}
}

void ANN_AIController::UpdateSightSense(AActor* Actor, FAIStimulus Stimulus)
{
	if (UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(),Stimulus)==UAISense_Sight::StaticClass())
	{
		if (Actor->ActorHasTag("Player") && Stimulus.WasSuccessfullySensed())
		{
			GetBlackboard()->SetValueAsBool("SeePlayer",true);
			GetBlackboard()->SetValueAsBool("IsHearSomething", true);
		}
		else
		{
			GetBlackboard()->SetValueAsBool("SeePlayer",false);
			GetBlackboard()->SetValueAsBool("IsHearSomething", false);
		}
	}
}

void ANN_AIController::UpdateHearingSense(AActor* Actor, FAIStimulus Stimulus)
{
	if (UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(),Stimulus)==UAISense_Hearing::StaticClass())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			GetBlackboard()->SetValueAsBool("IsHearSomething", true);
			GetBlackboard()->SetValueAsVector("SoundLocation",Stimulus.StimulusLocation);
			GetBlackboard()->SetValueAsEnum("EAIAction",1);
		}
		
	}
}

void ANN_AIController::UpdateTouchSense(AActor* Actor, FAIStimulus Stimulus)
{
	if (UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(),Stimulus)==UAISense_Touch::StaticClass())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			
			UE_LOG(LogTemp, Warning, TEXT("Touching"));
		}
	}
	
}
