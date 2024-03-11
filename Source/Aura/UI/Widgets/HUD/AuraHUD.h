// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aura/UI/WidgetController/AuraWidgetController.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraWidget;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:

	void InitHUD(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	UAuraWidgetController* GetWidgetController(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraWidget> AuraHUDWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraWidgetController> AuraWidgetControllerClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAuraWidget> AuraHUDWidget;
	
	UPROPERTY()
	TObjectPtr<UAuraWidgetController> AuraWidgetController;
};
