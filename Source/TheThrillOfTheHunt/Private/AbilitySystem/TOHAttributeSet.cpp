// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TOHAttributeSet.h"

#include <GameFramework/Character.h>
#include <GameplayEffectExtension.h>
#include <AbilitySystemBlueprintLibrary.h>
#include <Net/UnrealNetwork.h>
#include "TOHGameplayTags.h"


#define IMPLEMENT_TOH_ATTRIBUTE_REPL(Property) \
	void UTOHAttributeSet::OnRep_##Property(const FGameplayAttributeData& Old##Property) const \
	{ \
		GAMEPLAYATTRIBUTE_REPNOTIFY(UTOHAttributeSet, Property, Old##Property); \
	}

UTOHAttributeSet::UTOHAttributeSet()
{
	const FTOHGameplayTags& GameplayTags = FTOHGameplayTags::Get();

	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_BaseDamage, GetBaseDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_AttackSpeed, GetAttackSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_AttackRange, GetAttackRangeAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_AttackWidth, GetAttackWidthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_CritHitChance, GetCritHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_CritHitDamage, GetCritHitDamageAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Defensive_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Defensive_Health, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Defensive_MoveSpeed, GetMoveSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Defensive_DodgeCharges, GetDodgeChargesAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Defensive_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Defensive_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Defensive_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Defensive_Evasion, GetEvasionAttribute);
}

void UTOHAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UTOHAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UTOHAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);
}

void UTOHAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC)
		&& Props.SourceASC->AbilityActorInfo.IsValid()
		&& Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}
