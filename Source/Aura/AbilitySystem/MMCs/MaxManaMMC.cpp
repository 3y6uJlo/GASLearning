// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxManaMMC.h"

#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/Interact/CombatInterface.h"

UMaxManaMMC::UMaxManaMMC()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMaxManaMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluateParameters, Intelligence);
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int32 CharacterLevel = CombatInterface->GetCharacterLevel();
	
	return 50 + 2.5f * Intelligence + 15.f * CharacterLevel;
}
