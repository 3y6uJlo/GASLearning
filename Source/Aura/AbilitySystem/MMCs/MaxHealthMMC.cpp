// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxHealthMMC.h"


#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/Interact/CombatInterface.h"

UMaxHealthMMC::UMaxHealthMMC()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMaxHealthMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, Vigor);
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int32 CharacterLevel = CombatInterface->GetCharacterLevel();
	
	return 80 + 2.5f * Vigor + 10.f * CharacterLevel;
}
