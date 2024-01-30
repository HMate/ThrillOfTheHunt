// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/TOHUserWidget.h"

void UTOHUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
