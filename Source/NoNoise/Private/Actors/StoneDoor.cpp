
#include "Actors/StoneDoor.h"

#include "Actors/InteractActor_Valve.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStoneDoor::AStoneDoor()
{
	OpenDoorTL=CreateDefaultSubobject<UTimelineComponent>("OpenDoorTL");
	
}

void AStoneDoor::BeginPlay()
{
	Super::BeginPlay();
	if (!ValveActors.IsEmpty())
	{
		for (AInteractActor_Valve* Valve:ValveActors)
		{
			if (Valve)
				Valve->OnValveStateChanged.AddDynamic(this,&AStoneDoor::CheckPassword);
		}
		for (int i = 0; i < ValveActors.Num(); ++i)
		{
			Password_door.Add(0);
		}
	}
	if (OpenDoorTL)
	{
		FOnTimelineFloat OnUpdateDelegate;
		OnUpdateDelegate.BindUFunction(this,"OnTimelineUpdate");
		OpenDoorTL->AddInterpFloat(CF_OpenDoor,OnUpdateDelegate);
		
		FOnTimelineEvent OnFinishDelegate;
		OnFinishDelegate.BindUFunction(this,"OnTimelineFinished");
		OpenDoorTL->SetTimelineFinishedFunc(OnFinishDelegate);
		OpenDoorTL->SetPlayRate(1.0f);
		//OpenDoorTL->PlayFromStart();
	}
}

void AStoneDoor::CheckPassword(int32 ValveNumber, int32 ValvePassword)
{
	FString Password="";
	
	if (Password_door.IsValidIndex(ValveNumber-1))
	{
		Password_door[ValveNumber-1]=ValvePassword;
		for (int i = 0; i < Password_door.Num(); i++)
		{
			Password.Append(FString::FromInt(Password_door[i]));
		}
	}
	if (StoneDoorPassword==Password)
	{
		if (OpenStoneDoorSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				GetWorld(),
				OpenStoneDoorSound,
				GetActorLocation(),
				GetActorRotation(),
			1,
			1,
			0
			);
		}
		OpenDoorTL->PlayFromStart();
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
		2.f,
		FColor::Green,
		FString::Printf(TEXT("Valve:%s"),*Password)
		);
	}
}

void AStoneDoor::OnTimelineUpdate(float output)
{
	StartLocation=GetActorLocation();
	EndLocation=FVector(StartLocation.X,StartLocation.Y,output);
	FVector NewDoorLocation=FMath::Lerp(StartLocation,EndLocation,0.5f);
	SetActorLocation(NewDoorLocation);
}

void AStoneDoor::OnTimelineFinished()
{
	StoneDoorPassword="0000";
}

