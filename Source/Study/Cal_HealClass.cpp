// Fill out your copyright notice in the Description page of Project Settings.


#include "Cal_HealClass.h"
#include "MyAttributeSet.h"

UCal_HealClass::UCal_HealClass()
{
	HP.AttributeToCapture = UMyAttributeSet::GetHPAttribute();
	HP.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	HP.bSnapshot = false;

	MaxHP.AttributeToCapture = UMyAttributeSet::GetMaxHPAttribute();
	MaxHP.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	MaxHP.bSnapshot = false;

	RelevantAttributesToCapture.Add(HP);
	RelevantAttributesToCapture.Add(MaxHP);
}

float UCal_HealClass::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvalParam;
	EvalParam.SourceTags = SourceTags;
	EvalParam.TargetTags = TargetTags;

	float TempHP = 0;
	GetCapturedAttributeMagnitude(HP, Spec, EvalParam, TempHP);
	float TempMaxHP = 0;
	GetCapturedAttributeMagnitude(MaxHP, Spec, EvalParam, TempMaxHP);

	return FMath::Clamp(TempMaxHP-TempHP, 0, Heal_Point);
}
