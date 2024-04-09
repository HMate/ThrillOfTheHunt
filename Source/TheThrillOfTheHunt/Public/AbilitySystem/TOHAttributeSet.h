// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

#include "TOHAttributeSet.generated.h"

class UAbilitySystemComponent;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class THETHRILLOFTHEHUNT_API UTOHAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UTOHAttributeSet();

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data);

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	/*
	* Secondary Attributes
	*/

	UPROPERTY(BlueprintReadonly, Category = "Offensive Attributes")
	FGameplayAttributeData BaseDamage;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, BaseDamage);

	UPROPERTY(BlueprintReadonly, Category = "Offensive Attributes")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, AttackSpeed);

	UPROPERTY(BlueprintReadonly, Category = "Offensive Attributes")
	FGameplayAttributeData AttackRange;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, AttackRange);

	UPROPERTY(BlueprintReadonly, Category = "Offensive Attributes")
	FGameplayAttributeData AttackWidth;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, AttackWidth);

	UPROPERTY(BlueprintReadonly, Category = "Offensive Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, ArmorPenetration);

	UPROPERTY(BlueprintReadonly, Category = "Offensive Attributes")
	FGameplayAttributeData CritHitChance;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, CritHitChance);

	UPROPERTY(BlueprintReadonly, Category = "Offensive Attributes")
	FGameplayAttributeData CritHitDamage;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, CritHitDamage);

	/* Defensive */

	UPROPERTY(BlueprintReadonly, Category = "Defensive Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadonly, Category = "Defensive Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, Health);

	UPROPERTY(BlueprintReadonly, Category = "Defensive Attributes")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, MoveSpeed);

	UPROPERTY(BlueprintReadonly, Category = "Defensive Attributes")
	FGameplayAttributeData DodgeCharges;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, DodgeCharges);

	UPROPERTY(BlueprintReadonly, Category = "Defensive Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadonly, Category = "Defensive Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, Armor);

	UPROPERTY(BlueprintReadonly, Category = "Defensive Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, BlockChance);

	UPROPERTY(BlueprintReadonly, Category = "Defensive Attributes")
	FGameplayAttributeData Evasion;
	ATTRIBUTE_ACCESSORS(UTOHAttributeSet, Evasion);

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
