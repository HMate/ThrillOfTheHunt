// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TOHAssetManager.generated.h"

/**
 *
 */
UCLASS()
class THETHRILLOFTHEHUNT_API UTOHAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UTOHAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
