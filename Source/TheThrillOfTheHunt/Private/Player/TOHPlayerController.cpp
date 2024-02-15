// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TOHPlayerController.h"

#include <EnhancedInputSubsystems.h>
#include <AbilitySystemBlueprintLibrary.h>
#include "AbilitySystem/TOHAbilitySystemComponent.h"
#include "Input/TOHInputComponent.h"


ATOHPlayerController::ATOHPlayerController()
{
	bReplicates = true;
}

void ATOHPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(TOHContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(TOHContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ATOHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UTOHInputComponent* IC = CastChecked<UTOHInputComponent>(InputComponent);

	IC->BindAbilityActions(InputConfig, this,
		&ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);

}

void ATOHPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, *InputTag.ToString());
}

void ATOHPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ATOHPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UTOHAbilitySystemComponent* ATOHPlayerController::GetASC()
{
	if (TOHAbilitySystemComponent == nullptr)
	{
		TOHAbilitySystemComponent = Cast<UTOHAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return TOHAbilitySystemComponent.Get();
}
