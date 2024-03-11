// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraCharacterBase.h"

#include "AbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), "WeaponHandSocket");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::InitializeAttributes()
{
	ApplyEffectToSelf(InitializePrimaryAttributesEffect);
	ApplyEffectToSelf(InitializeSecondaryAttributesEffect);
	ApplyEffectToSelf(InitializeVitalAttributesEffect);
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float Level)
{
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle InitializeEffectSpec = AbilitySystemComponent->MakeOutgoingSpec(Effect, Level, EffectContext);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*InitializeEffectSpec.Data.Get(), AbilitySystemComponent);
}
