
#include "Actors/InteractActor_Valve.h"

#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"
#include "Game/NNPlayerController.h"
#include "Kismet/GameplayStatics.h"

AInteractActor_Valve::AInteractActor_Valve()
{
	SceneComponent=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	Valve=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Valve"));
	Valve->SetupAttachment(RootComponent);
	TriggerBox=CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TimelineComp=CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComp"));
	
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this,&AInteractActor_Valve::OnBoxTriggerBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this,&AInteractActor_Valve::OnBoxTriggerEnd);
	
	PromptWidgetComp=CreateDefaultSubobject<UWidgetComponent>(TEXT("PromptWidgetComp"));
	PromptWidgetComp->SetupAttachment(RootComponent);
	
	StartValue=0.0f;
	EndValue=0.0f;
	ValvePassword=2;
}

void AInteractActor_Valve::BeginPlay()
{
	Super::BeginPlay();
	
	FOnTimelineFloat OnUpdateDelegate;
	OnUpdateDelegate.BindUFunction(this,"OnTimelineUpdate");
	TimelineComp->AddInterpFloat(CF_Valve,OnUpdateDelegate);
	
	FOnTimelineEvent OnFinishedDelegate;
	OnFinishedDelegate.BindUFunction(this,"OnTimelineFinished");
	TimelineComp->SetTimelineFinishedFunc(OnFinishedDelegate);
	TimelineComp->SetPlayRate(1.0f);
	
	NNPC=Cast<ANNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (NNPC)
	{
		NNPC->OnTabPressed.AddDynamic(this,&AInteractActor_Valve::ChangeValveState);
	}
}

void AInteractActor_Valve::ChangeValve()
{
	OnValveStateChanged.Broadcast(ValveNumber,ValvePassword);
}

void AInteractActor_Valve::OnTimelineUpdate(float output)
{
	float RotationValue=FMath::Lerp(StartValue,EndValue,output);
	Valve->SetRelativeRotation(FRotator(RotationValue,0,0));
}

void AInteractActor_Valve::OnTimelineFinished()
{
	StartValue=EndValue;
	CanUseValve=true;
	if (IsTurnRight)
	{
		ValvePassword++;
	}
	else
	{
		ValvePassword--;
	}
	ChangeValve();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
		2.f,
		FColor::Green,
		FString::Printf(TEXT("%d"),ValvePassword)
		);
	}
}

void AInteractActor_Valve::OnBoxTriggerBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		if (NNPC)
		{
			NNPC->InteractActor_ValveRef=this;
			NNPC->bTurnRight=IsTurnRight;
		}
		PromptWidgetComp->SetVisibility(true);
		CanUseValve=true;
		
		UE_LOG(LogTemp,Warning,TEXT("%d"),IsTurnRight);
	}
}

void AInteractActor_Valve::OnBoxTriggerEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*if (OtherActor->ActorHasTag("Player"))
	{
		PromptWidgetComp->SetVisibility(false);
	}*/
}

void AInteractActor_Valve::ChangeValveState(bool bIsTurnRight)
{
	if (bIsTurnRight)
	{
		IsTurnRight=true;
	}
	else
	{
		IsTurnRight=false;
	}
}

void AInteractActor_Valve::Interact() const
{
	Super::Interact();
}

void AInteractActor_Valve::Interact_Implementation()
{
	Super::Interact_Implementation();
	
	if (CanUseValve)
	{
		if (IsTurnRight)
		{
			/*if (ValvePassword==2)
			{
				EndValue=90.0f;
			}
			else
			{
				EndValue-=90.f;
			}*/
			if (ValvePassword<4)
			{
				EndValue-=90.0f;
				TimelineComp->PlayFromStart();
				CanUseValve=false;
			}
		}
		else
		{
			/*if (ValvePassword==2)
			{
				EndValue=90.0f;
			}
			else
			{
				EndValue+=90.f;
			}*/
			if (ValvePassword>0)
			{
				EndValue+=90.0f;
				TimelineComp->PlayFromStart();
				ChangeValve();
				CanUseValve=false;
			}
		}
	}
	
}
