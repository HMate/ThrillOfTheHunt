// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/TOHAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "TOHGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	const UTOHAttributeSet* AS = CastChecked<UTOHAttributeSet>(AttributeSet);

	check(AttributeInfo);

	FTOHAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FTOHGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}
