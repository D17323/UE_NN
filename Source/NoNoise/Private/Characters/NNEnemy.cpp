// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NNEnemy.h"

#include "Perception/AISense_Touch.h"

ANNEnemy::ANNEnemy()
{
	TouchBox=CreateDefaultSubobject<UBoxComponent>(TEXT("TouchBox"));
	TouchBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TouchBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TouchBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TouchBox->SetupAttachment(RootComponent);
	TouchBox->OnComponentBeginOverlap.AddDynamic(this,&ANNEnemy::OnTouchBegin);
}

void ANNEnemy::OnTouchBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		UAISense_Touch::ReportTouchEvent(GetWorld(),this,OtherActor,GetActorLocation());
	}
	
}
