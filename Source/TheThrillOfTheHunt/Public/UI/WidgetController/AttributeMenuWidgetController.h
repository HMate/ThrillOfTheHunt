// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/TOHWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 *
 */
UCLASS()
class THETHRILLOFTHEHUNT_API UAttributeMenuWidgetController : public UTOHWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

};
