
#include "Actors/InteractActorsBase.h"

void AInteractActorsBase::Interact() const
{
}

void AInteractActorsBase::Interact_Implementation()
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
		2.f,
		FColor::Green,
		FString::Printf(TEXT("adsada"))
		);
	}*/
	UE_LOG(LogTemp,Warning,TEXT("InterfaceOk"));
}
