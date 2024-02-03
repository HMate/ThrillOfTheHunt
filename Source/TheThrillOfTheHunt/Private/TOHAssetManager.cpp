// Fill out your copyright notice in the Description page of Project Settings.


#include "TOHAssetManager.h"
#include <TOHGameplayTags.h>

UTOHAssetManager& UTOHAssetManager::Get()
{
	check(GEngine);

	UTOHAssetManager* Manager = Cast<UTOHAssetManager>(GEngine->AssetManager);
	return *Manager;
}

void UTOHAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FTOHGameplayTags::InitializeNativeGameplayTags();
}
