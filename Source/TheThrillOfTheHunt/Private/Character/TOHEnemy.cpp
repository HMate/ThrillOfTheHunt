// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TOHEnemy.h"

#include "AbilitySystem/TOHAbilitySystemComponent.h"
#include "AbilitySystem/TOHAttributeSet.h"

ATOHEnemy::ATOHEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTOHAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);


	AttributeSet = CreateDefaultSubobject<UTOHAttributeSet>("AttributeSet");
}

int32 ATOHEnemy::GetPlayerLevel()
{
	return Level;
}

void ATOHEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void ATOHEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UTOHAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}
