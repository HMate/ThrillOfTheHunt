// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TOHAbilitySystemComponent.h"
#include <TOHGameplayTags.h>

void UTOHAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UTOHAbilitySystemComponent::EffectApplied);

	const FTOHGameplayTags& GameplayTags = FTOHGameplayTags::Get();

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange,
		FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString()));
}

void UTOHAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
