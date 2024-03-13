// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TOHPlayerController.h"

#include <EnhancedInputSubsystems.h>
#include <AbilitySystemBlueprintLibrary.h>
#include "AbilitySystem/TOHAbilitySystemComponent.h"
#include "Input/TOHInputComponent.h"
#include "TOHGameplayTags.h"
#include <Interaction/EnemyInterface.h>


ATOHPlayerController::ATOHPlayerController()
{
	bReplicates = true;
}

void ATOHPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void ATOHPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(TOHContext);

	auto LocalPlayer = GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	// TODO: On clients LocalPlayer is null at this point. But BeginPlay is called twice on client, and by the second time it is set.
	// If this would be a problem, based on some code exploration, we should set the mapping context in the GameMode postlogin function.
	if (Subsystem)
	{
		check(Subsystem);
		Subsystem->AddMappingContext(TOHContext, 0);

		bShowMouseCursor = true;
		DefaultMouseCursor = EMouseCursor::Default;

		FInputModeGameAndUI InputModeData;
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputModeData.SetHideCursorDuringCapture(false);
		SetInputMode(InputModeData);
	}
}

void ATOHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UTOHInputComponent* IC = CastChecked<UTOHInputComponent>(InputComponent);

	IC->BindAbilityActions(InputConfig, this,
		&ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);

}

void ATOHPlayerController::CursorTrace()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (!Hit.bBlockingHit)
		return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(Hit.GetActor());
}

void ATOHPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FTOHGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
	}

	if (InputTag.MatchesTagExact(FTOHGameplayTags::Get().InputTag_Shift))
	{
		bShiftKeyDown = true;
	}
}

void ATOHPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	if (!InputTag.MatchesTagExact(FTOHGameplayTags::Get().InputTag_LMB))
	{
		GetASC()->AbilityInputTagReleased(InputTag);
	}

	if (InputTag.MatchesTagExact(FTOHGameplayTags::Get().InputTag_Shift))
	{
		bShiftKeyDown = true;
	}

	GetASC()->AbilityInputTagReleased(InputTag);
}

void ATOHPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	if (!InputTag.MatchesTagExact(FTOHGameplayTags::Get().InputTag_LMB))
	{
		GetASC()->AbilityInputTagHeld(InputTag);
	}

	if (bTargeting || bShiftKeyDown)
	{
		GetASC()->AbilityInputTagHeld(InputTag);
	}
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
