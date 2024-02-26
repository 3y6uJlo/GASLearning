// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AEffectActor::AEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AEffectActor::ApplyEffectsToTarget(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetActor || !TargetAbilitySystemComponent)
		return;

	for (TSubclassOf<UGameplayEffect> AppliedEffectClass : AppliedEffectsClass)
	{
		FGameplayEffectContextHandle EffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(AppliedEffectClass, EffectLevel, EffectContextHandle);
		FActiveGameplayEffectHandle EffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		if (EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
		{
			InfiniteEffectsHandles.Add(EffectHandle, TargetAbilitySystemComponent);
		}
	}
	
}

void AEffectActor::RemoveInfiniteEffects(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetActor || !TargetAbilitySystemComponent)
		return;

	TArray<FActiveGameplayEffectHandle> HandlesToRemove; 
	for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> EffectHandle : InfiniteEffectsHandles)
	{
		if (EffectHandle.Value == TargetAbilitySystemComponent)
		{
			TargetAbilitySystemComponent->RemoveActiveGameplayEffect(EffectHandle.Key, 1);
			HandlesToRemove.Add(EffectHandle.Key);
		}
	}
	for (FActiveGameplayEffectHandle HandleToRemove : HandlesToRemove)
	{
		InfiniteEffectsHandles.FindAndRemoveChecked(HandleToRemove);
	}
}

