// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/TOHInputConfig.h"
#include <memory>

const UInputAction* UTOHInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FTOHInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]."),
			*InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
