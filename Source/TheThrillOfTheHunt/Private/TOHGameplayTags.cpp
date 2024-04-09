// Fill out your copyright notice in the Description page of Project Settings.


#include "TOHGameplayTags.h"
#include <GameplayTagsManager.h>


FTOHGameplayTags FTOHGameplayTags::GameplayTags;

void FTOHGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Offensive_BaseDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Offensive.BaseDamage"), FString("Increases physical damage of main attack"));
	GameplayTags.Attributes_Offensive_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Offensive.AttackSpeed"), FString("Attack speed of main attack"));
	GameplayTags.Attributes_Offensive_AttackRange = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Offensive.AttackRange"), FString("Attack range of main attack"));
	GameplayTags.Attributes_Offensive_AttackWidth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Offensive.AttackWidth"), FString("Width of cone for main attack in degrees."));
	GameplayTags.Attributes_Offensive_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Offensive.ArmorPenetration"), FString("Percentage amount to ignore from enemy armor"));
	GameplayTags.Attributes_Offensive_CritHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Offensive.CritHitChance"), FString("Chance to inflict plus critical hit damage"));
	GameplayTags.Attributes_Offensive_CritHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Offensive.CritHitDamage"), FString("Bonus damage added when a critical hit is scored"));

	GameplayTags.Attributes_Defensive_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Defensive.MaxHealth"), FString("The maximum amount of Health the character can have"));
	GameplayTags.Attributes_Defensive_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Defensive.Health"), FString("Current health of character. Player dies if it hits zero."));
	GameplayTags.Attributes_Defensive_MoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Defensive.MoveSpeed"), FString("Unreal units of speed moved by character while walking,"));
	GameplayTags.Attributes_Defensive_DodgeCharges = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Defensive.DodgeCharges"), FString("How many times can the character dodge without waiting cooldowns"));
	GameplayTags.Attributes_Defensive_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Defensive.HealthRegeneration"), FString("Amount of Health regenerated every 1 second"));
	GameplayTags.Attributes_Defensive_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Defensive.Armor"), FString("Reduces damage taken"));
	GameplayTags.Attributes_Defensive_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Defensive.BlockChance"), FString("Chance to cut incoming damage in half"));
	GameplayTags.Attributes_Defensive_Evasion = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Defensive.Evasion"), FString("Gives chance to evade an attack completely"));

	/* Input Tags */
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"), FString("Input tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"), FString("Input tag for Right Mouse Button"));
	GameplayTags.InputTag_Dodge = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Dodge"), FString("Input tag for dodge ability"));
	GameplayTags.InputTag_Shift = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Shift"), FString("Input tag for Shift"));
}
