// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TOHHUD.h"

#include "UI/Widget/TOHUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include <UI/WidgetController/AttributeMenuWidgetController.h>

UOverlayWidgetController* ATOHHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* ATOHHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	checkf(AttributeMenuWidgetControllerClass, TEXT("AttributeMenu Widget Controller Class is uninitialized, please fill out BP_TOHHUD"));
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

void ATOHHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class is uninitialized, please fill out BP_TOHHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class is uninitialized, please fill out BP_TOHHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UTOHUserWidget>(Widget);

	const FWidgetControllerParams WCParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WCParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

