// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NNCharacterBase.h"
#include "Components/BoxComponent.h"
#include "NNEnemy.generated.h"

/**
 * 
 */
UCLASS()
class NONOISE_API ANNEnemy : public ANNCharacterBase
{
	GENERATED_BODY()

protected:
	ANNEnemy();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* TouchBox;
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PartolPoints")
	TArray<AActor*> PatrolPoints;
	
private:
	UFUNCTION()
	void OnTouchBegin(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult & SweepResult);
};
