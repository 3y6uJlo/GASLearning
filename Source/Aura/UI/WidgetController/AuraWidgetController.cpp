// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraWidgetController.h"

#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"

void UAuraWidgetController::InitParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,
                                       UAttributeSet* AS)
{
	PlayerController = PC;
	PlayerState = PS;
	AbilityComponent = ASC;
	AttributeSet = AS;
}

void UAuraWidgetController::BroadcastInitValues()
{
	UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	OnHealthChange.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChange.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChange.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChange.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UAuraWidgetController::BindAttributesChangesCallbacks()
{
	UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChange.Broadcast(Data.NewValue);
		}
	);
	
	Cast<UAuraAbilitySystemComponent>(AbilityComponent)->OnMessageTags.AddLambda(
		[this](const FGameplayTagContainer GameplayTagContainer)
		{
			checkf(MessageWidgetDataTable, TEXT("DataTable is null"));
			for (FGameplayTag MessageTag : GameplayTagContainer)
			{
				OnMessage.Broadcast(*GetTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, MessageTag));
			}
		}
	);
	
	BindPrimaryAttributesCallbacks(AuraAttributeSet);
	BindSecondaryAttributesCallbacks(AuraAttributeSet);
}

void UAuraWidgetController::BindPrimaryAttributesCallbacks(UAuraAttributeSet* AuraAttributeSet)
{
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetStrengthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnStrengthChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetIntelligenceAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnIntelligenceChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetResilienceAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnResilienceChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetVigorAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnVigorChange.Broadcast(Data.NewValue);
		}
	);
}

void UAuraWidgetController::BindSecondaryAttributesCallbacks(UAuraAttributeSet* AuraAttributeSet)
{
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetArmorAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnArmorChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetArmorPenetrationAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnArmorPenetrationChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetBlockChanceAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnBlockChanceChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetCriticalHitChanceAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnCriticalHitChanceChange.Broadcast(Data.NewValue);
		}
	);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetCriticalHitResistanceAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnCriticalHitResistanceChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetCriticalHitDamageAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnCriticalHitDamageChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthRegenerationAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthRegenerationChange.Broadcast(Data.NewValue);
		}
	);

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaRegenerationAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaRegenerationChange.Broadcast(Data.NewValue);
		}
	);
}
