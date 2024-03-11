// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	int32 GetCharacterLevel() const { return CharacterLevel; }
	
protected:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CharacterLevel)
	int32 CharacterLevel = 1.f;

	UFUNCTION()
	void OnRep_CharacterLevel();
};
