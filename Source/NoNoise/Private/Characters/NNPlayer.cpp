// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NNPlayer.h"

#include "KismetTraceUtils.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Interfaces/InteractInterface.h"
#include "Kismet/KismetSystemLibrary.h"

ANNPlayer::ANNPlayer()
{
	PlayerAudio=CreateDefaultSubobject<UAudioComponent>("PlayerAudio");
	//FlashLight=CreateDefaultSubobject<USpotLightComponent>("FlashLight");
}

void ANNPlayer::OnInteract()
{
	if (PlayerCamera)
	{
		FVector StartLocation = PlayerCamera->GetComponentLocation();
		FVector EndLocation=StartLocation+PlayerCamera->GetForwardVector()*300.0f;
		
		FHitResult HitResult;
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(this);
		
		bool hit=GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECC_Visibility,
			CollisionQueryParams
			);
		if (hit)
		{
			AActor* HitActor = HitResult.GetActor();
			IInteractInterface* InteractInterface=Cast<IInteractInterface>(HitActor);
			if (InteractInterface)
			{
				InteractInterface->Interact_Implementation();
			}
			
			DrawDebugLineTraceSingle(
				GetWorld(),
				StartLocation,
				EndLocation,
				EDrawDebugTrace::ForDuration,
				hit,
				HitResult,
				FColor::Green,
				FColor::Red,
				5.0f
				);
			UE_LOG(LogTemp,Warning,TEXT("%s"),*HitResult.GetActor()->GetName());
		}
	}
	
}

