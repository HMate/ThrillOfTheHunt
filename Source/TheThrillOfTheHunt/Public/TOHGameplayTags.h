// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * TOHGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */
struct FTOHGameplayTags
{
public:
	static const FTOHGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	/* Offensive Attributes */
	FGameplayTag Attributes_Offensive_BaseDamage;
	FGameplayTag Attributes_Offensive_AttackSpeed;
	FGameplayTag Attributes_Offensive_AttackRange;
	FGameplayTag Attributes_Offensive_AttackWidth;
	FGameplayTag Attributes_Offensive_ArmorPenetration;
	FGameplayTag Attributes_Offensive_CritHitChance;
	FGameplayTag Attributes_Offensive_CritHitDamage;
	/* Defensive Attributes */
	FGameplayTag Attributes_Defensive_MaxHealth;
	FGameplayTag Attributes_Defensive_Health;
	FGameplayTag Attributes_Defensive_MoveSpeed;
	FGameplayTag Attributes_Defensive_DodgeCharges;
	FGameplayTag Attributes_Defensive_HealthRegeneration;
	FGameplayTag Attributes_Defensive_Armor;
	FGameplayTag Attributes_Defensive_BlockChance;
	FGameplayTag Attributes_Defensive_Evasion;
	/* Vital Attributes */

	/* Input Tags */
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_Shift;
	FGameplayTag InputTag_Dodge;

private:
	static FTOHGameplayTags GameplayTags;
};
