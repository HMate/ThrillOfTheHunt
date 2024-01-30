// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TOHPlayerState.h"

#include <AbilitySystem/TOHAbilitySystemComponent.h>
#include <AbilitySystem/TOHAttributeSet.h>

ATOHPlayerState::ATOHPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTOHAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UTOHAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ATOHPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ATOHPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
