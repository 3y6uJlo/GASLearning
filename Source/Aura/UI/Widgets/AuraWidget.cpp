// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraWidget.h"

void UAuraWidget::SetWidgetController(UAuraWidgetController* AuraWidgetController)
{
	WidgetController = AuraWidgetController;
	OnSetWidgetController();
}
