// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NNCharacterBase.h"


ANNCharacterBase::ANNCharacterBase()
{
	bUseControllerRotationPitch=true;
	bUseControllerRotationYaw=true;
	bUseControllerRotationRoll=false;
}

void ANNCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}




