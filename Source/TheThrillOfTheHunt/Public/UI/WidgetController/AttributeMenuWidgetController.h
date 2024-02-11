// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/TOHWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

struct FTOHAttributeInfo;
class UAttributeInfo;
struct FGameplayTag;
struct FGameplayAttribute;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FTOHAttributeInfo&, Info);

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class THETHRILLOFTHEHUNT_API UAttributeMenuWidgetController : public UTOHWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
