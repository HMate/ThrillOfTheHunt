// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TOHAbilitySystemLibrary.h"
#include <Kismet/GameplayStatics.h>

#include "UI/WidgetController/TOHWidgetController.h"
#include "UI/HUD/TOHHUD.h"
#include "Player/TOHPlayerState.h"

UOverlayWidgetController* UTOHAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (auto* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ATOHHUD* Hud = Cast<ATOHHUD>(PC->GetHUD()))
		{
			ATOHPlayerState* PS = PC->GetPlayerState<ATOHPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return Hud->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UTOHAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (auto* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ATOHHUD* Hud = Cast<ATOHHUD>(PC->GetHUD()))
		{
			ATOHPlayerState* PS = PC->GetPlayerState<ATOHPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return Hud->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
