// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TOHEnemy.h"

#include "AbilitySystem/TOHAbilitySystemComponent.h"
#include "AbilitySystem/TOHAttributeSet.h"
#include <Components/WidgetComponent.h>
#include "UI/Widget/TOHUserWidget.h"

ATOHEnemy::ATOHEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTOHAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UTOHAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

int32 ATOHEnemy::GetPlayerLevel()
{
	return Level;
}

void ATOHEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	if (UTOHUserWidget* TOHUserWidget = Cast<UTOHUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		TOHUserWidget->SetWidgetController(this);
	}
	BindCallbacksToDependencies();
	BroadcastInitialValues();
}

void ATOHEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UTOHAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void ATOHEnemy::BroadcastInitialValues()
{
	const UTOHAttributeSet* Attributes = CastChecked<UTOHAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(Attributes->GetHealth());
	OnMaxHealthChanged.Broadcast(Attributes->GetMaxHealth());
}

void ATOHEnemy::BindCallbacksToDependencies()
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
}
