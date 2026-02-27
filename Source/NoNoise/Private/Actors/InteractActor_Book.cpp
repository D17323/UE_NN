
#include "Actors/InteractActor_Book.h"

#include "Components/WidgetComponent.h"


AInteractActor_Book::AInteractActor_Book()
{
	SceneComponent=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent=SceneComponent;
	Book=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Book"));
	Book->SetupAttachment(RootComponent);
	PromptWidgetComp=CreateDefaultSubobject<UWidgetComponent>(TEXT("PromptWidgetComp"));
	PromptWidgetComp->SetupAttachment(RootComponent);
}

void AInteractActor_Book::Interact() const
{
	Super::Interact();
}

void AInteractActor_Book::Interact_Implementation()
{
	Super::Interact_Implementation();
	
	SetActorHiddenInGame(true);
	if (PromptWidgetComp)
	{
		PromptWidgetComp->SetVisibility(false);
	}
	bIsPicked=true;
	
}
