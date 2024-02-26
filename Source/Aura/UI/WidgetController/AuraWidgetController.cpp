// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraWidgetController.h"

#include "Aura/AbilitySystem/AuraAttributeSet.h"

void UAuraWidgetController::InitParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
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
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
			.AddUObject(this, &UAuraWidgetController::HealthChanged);
	
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
			.AddUObject(this, &UAuraWidgetController::MaxHealthChanged);
	
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
			.AddUObject(this, &UAuraWidgetController::ManaChanged);
	
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
			.AddUObject(this, &UAuraWidgetController::MaxManaChanged);
}

void UAuraWidgetController::HealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChange.Broadcast(Data.NewValue);
}

void UAuraWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChange.Broadcast(Data.NewValue);
}

void UAuraWidgetController::ManaChanged(const FOnAttributeChangeData& Data)
{
	OnManaChange.Broadcast(Data.NewValue);
}

void UAuraWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	OnMaxManaChange.Broadcast(Data.NewValue);
}
