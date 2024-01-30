// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TOHCharacterBase.h"
#include "TOHEnemy.generated.h"

/**
 *
 */
UCLASS()
class THETHRILLOFTHEHUNT_API ATOHEnemy : public ATOHCharacterBase
{
	GENERATED_BODY()

public:
	ATOHEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
