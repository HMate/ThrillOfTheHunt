// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"

#include "TOHPlayerController.generated.h"

class IEnemyInterface;
class UTOHInputConfig;
class UInputMappingContext;
class UTOHAbilitySystemComponent;

/**
 *
 */
UCLASS()
class THETHRILLOFTHEHUNT_API ATOHPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATOHPlayerController();
	virtual void PlayerTick(float DeltaTime);
protected:
	virtual void BeginPlay();
	virtual void SetupInputComponent();
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> TOHContext;

	void CursorTrace();
	IEnemyInterface* ThisActor;
	IEnemyInterface* LastActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UTOHInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UTOHAbilitySystemComponent> TOHAbilitySystemComponent;

	UTOHAbilitySystemComponent* GetASC();

	bool bTargeting = false;
};
