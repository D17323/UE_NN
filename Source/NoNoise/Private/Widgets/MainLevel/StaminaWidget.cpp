// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainLevel/StaminaWidget.h"

#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

UStaminaWidget::UStaminaWidget(const FObjectInitializer& OI):Super(OI)
{
	StaminaValue=100.0f;
	CurrentValue_Severity=0.0f;
	reduceValue=0.0f;
}

void UStaminaWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	NNPC=Cast<ANNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	
	if (Stamina_pb)
		Stamina_pb->SetPercent(0);
	if (Severity_pb)
		Severity_pb->SetPercent(0);
	
}

void UStaminaWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	SetStaminaPB();
}

void UStaminaWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (SeverityTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(SeverityTimer);
	}
}

void UStaminaWidget::SetStaminaPB()
{
	if (NNPC)
	{
		StaminaValue=NNPC->CurrentStamina;
		Stamina_pb->SetPercent(StaminaValue/100.0f);
	}
}

void UStaminaWidget::SetSeverityPB(float Value)
{
	Severity_pb->SetPercent(Value/100.0f);
}


