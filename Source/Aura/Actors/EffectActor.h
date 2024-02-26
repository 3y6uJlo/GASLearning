// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

struct FActiveGameplayEffectHandle;
class UGameplayEffect;
UCLASS()
class AURA_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AEffectActor();

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectsToTarget(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void RemoveInfiniteEffects(AActor* TargetActor);

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> AppliedEffectsClass;

	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> InfiniteEffectsHandles;

	UPROPERTY(EditAnywhere)
	float EffectLevel = 1.f;

};
