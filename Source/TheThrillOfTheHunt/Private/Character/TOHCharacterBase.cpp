// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TOHCharacterBase.h"

#include "AbilitySystemComponent.h"


ATOHCharacterBase::ATOHCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATOHCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void ATOHCharacterBase::InitAbilityActorInfo()
{
}

UAbilitySystemComponent* ATOHCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ATOHCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ATOHCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	check(IsValid(ASC));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle =
		ASC->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle =
		ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, ASC);
}

void ATOHCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}
