// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "Cal_HealClass.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API UCal_HealClass : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UCal_HealClass();

	virtual float CalculateBaseMagnitude_Implementation(const
		FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition HP;
	FGameplayEffectAttributeCaptureDefinition MaxHP;

	float Heal_Point = 100.0f;
};
