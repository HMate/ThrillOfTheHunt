// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include <AbilitySystem/TOHAttributeSet.h>
#include <AbilitySystem/TOHAbilitySystemComponent.h>

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UTOHAttributeSet* Attributes = CastChecked<UTOHAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(Attributes->GetHealth());
	OnMaxHealthChanged.Broadcast(Attributes->GetMaxHealth());
	OnDodgeChargesChanged.Broadcast(Attributes->GetDodgeCharges());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UTOHAttributeSet* Attributes = CastChecked<UTOHAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetDodgeChargesAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnDodgeChargesChanged.Broadcast(Data.NewValue);
			});

	Cast<UTOHAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			for (const FGameplayTag& Tag : AssetTags)
			{
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}
