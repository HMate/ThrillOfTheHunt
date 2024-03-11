// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystem/TOHAbilitySystemComponent.h"
#include <Player/TOHPlayerController.h>

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	APlayerController* Controller = Ability->GetCurrentActorInfo()->PlayerController.Get();
	check(Controller);

	FHitResult Hit;
	Controller->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	ValidData.Broadcast(Hit.ImpactPoint);
}
