// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraWidget.generated.h"

class UAuraWidgetController;

UCLASS()
class AURA_API UAuraWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UAuraWidgetController* AuraWidgetController);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSetWidgetController();
	
protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAuraWidgetController> WidgetController;
	
};
