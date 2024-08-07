// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class STUDY_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, HP);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxHP);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MP);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxMP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxMP);
};
