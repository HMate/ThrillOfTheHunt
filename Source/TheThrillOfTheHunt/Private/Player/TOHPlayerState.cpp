// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TOHPlayerState.h"

#include <AbilitySystem/TOHAbilitySystemComponent.h>
#include <AbilitySystem/TOHAttributeSet.h>
#include "AttributeSet.h"
#include <Net/UnrealNetwork.h>

ATOHPlayerState::ATOHPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTOHAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UTOHAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void ATOHPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATOHPlayerState, Level);
}

UAbilitySystemComponent* ATOHPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ATOHPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

void ATOHPlayerState::OnRep_Level(int32 OldLevel)
{

}
