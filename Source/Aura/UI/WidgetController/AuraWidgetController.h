// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Aura/UI/Widgets/AuraWidget.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAuraAttributeSet;
struct FOnAttributeChangeData;
class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageSignature, const FUIWidgetRow&, MessageRow);



UCLASS(BlueprintType, Blueprintable)
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	
	 void InitParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	void BroadcastInitValues();

	void BindAttributesChangesCallbacks();

	void BindPrimaryAttributesCallbacks(UAuraAttributeSet* AuraAttributeSet);
	void BindSecondaryAttributesCallbacks(UAuraAttributeSet* AuraAttributeSet);
	
	
protected:

	template <typename T>
	T* GetTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxHealthChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnManaChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxManaChange;

	// Primary Attributes callbacks
	//

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnStrengthChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnIntelligenceChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnResilienceChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnVigorChange;
	
	//
	// End Primary Attributes callbacks

	// Secondary Attributes callbacks
	//

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnArmorChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnArmorPenetrationChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnBlockChanceChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnCriticalHitChanceChange;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnCriticalHitResistanceChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnCriticalHitDamageChange;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthRegenerationChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnManaRegenerationChange;
	
	//
	// End Secondary Attributes callbacks

	UPROPERTY(BlueprintAssignable)
	FOnMessageSignature OnMessage;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilityComponent;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAttributeSet> AttributeSet;
};

template <typename T>
T* UAuraWidgetController::GetTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
