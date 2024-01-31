// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TOHCharacterBase.h"
#include "TOHCharacter.generated.h"

UCLASS()
class THETHRILLOFTHEHUNT_API ATOHCharacter : public ATOHCharacterBase
{
	GENERATED_BODY()
public:
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	/** Combar Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combar Interface */

private:
	virtual void InitAbilityActorInfo() override;
};
