// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraHUD.h"
#include "Aura/UI/Widgets/AuraWidget.h"
#include "Blueprint/UserWidget.h"

void AAuraHUD::InitHUD(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	check(PC);
	check(PS);
	check(ASC);
	check(AS);
	AuraWidgetController = GetWidgetController(PC, PS, ASC, AS);

	AuraHUDWidget = CreateWidget<UAuraWidget>(GetWorld(), AuraHUDWidgetClass);
	AuraHUDWidget->SetWidgetController(AuraWidgetController);

	AuraWidgetController->BroadcastInitValues();
	AuraHUDWidget->AddToViewport();
}

UAuraWidgetController* AAuraHUD::GetWidgetController(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	if (!AuraWidgetController)
	{
		AuraWidgetController = NewObject<UAuraWidgetController>(this, UAuraWidgetController::StaticClass());
		AuraWidgetController->InitParams(PC, PS, ASC, AS);

		AuraWidgetController->BindAttributesChangesCallbacks();
	}
	return AuraWidgetController;
}
