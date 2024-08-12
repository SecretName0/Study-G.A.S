// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecutionCalculation.h"
#include "MyAttributeSet.h"

struct DamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(HP);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHP);

	DECLARE_ATTRIBUTE_CAPTUREDEF(MP);

	DamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, HP, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, MaxHP, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, MP, Source, false);
	}
};

static DamageCapture& GetDamageCapture()
{
	static DamageCapture DamageCapture;
	return DamageCapture;
}

UExecutionCalculation::UExecutionCalculation()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().HPDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().MaxHPDef);

	RelevantAttributesToCapture.Add(GetDamageCapture().MPDef);
}

void UExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* SourceGAS = ExecutionParams.GetSourceAbilitySystemComponent();
	AActor* SourceActor = SourceGAS ? SourceGAS->GetAvatarActor() : nullptr;

	UAbilitySystemComponent* TargetGAS = ExecutionParams.GetTargetAbilitySystemComponent();
	AActor* TargetActor = TargetGAS ? TargetGAS->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = SourceTags;
	EvalParams.TargetTags = TargetTags;

	float Cal_HP = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().HPDef,
		EvalParams, Cal_HP);

	float Cal_MaxHP = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().MaxHPDef,
		EvalParams, Cal_MaxHP);

	float Cal_MP = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().MPDef,
		EvalParams, Cal_MP);

	float AddHP = FMath::Clamp(Cal_MaxHP - Cal_HP, 0, HealPoint);

	TargetGAS->ApplyModToAttribute(UMyAttributeSet::GetHPAttribute(), EGameplayModOp::Additive,
		AddHP);

	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(GetDamageCapture().MPProperty, EGameplayModOp::Additive,
			-AddHP));
}
