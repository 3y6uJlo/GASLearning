// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Aura/Interact/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	
	virtual void InitAbilityActorInfo(){};

	void InitializeAttributes();
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float Level = 1.f);

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> InitializePrimaryAttributesEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> InitializeSecondaryAttributesEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> InitializeVitalAttributesEffect;
};
