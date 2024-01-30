// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TOHCharacter.h"

#include "AbilitySystem/TOHAbilitySystemComponent.h"
#include "Player/TOHPlayerState.h"
#include "Player/TOHPlayerController.h"
#include <UI/HUD/TOHHUD.h>


void ATOHCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the server
	InitAbilityActorInfo();
}

void ATOHCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	/* Init ability actor info for the client.
	This gets called after controller posessed the pawn and its replicated to client,
	so we can set the actor info here the soonest*/
	InitAbilityActorInfo();
}

void ATOHCharacter::InitAbilityActorInfo()
{
	ATOHPlayerState* PState = GetPlayerState<ATOHPlayerState>();
	check(PState);

	PState->GetAbilitySystemComponent()->InitAbilityActorInfo(PState, this);
	AbilitySystemComponent = PState->GetAbilitySystemComponent();
	AttributeSet = PState->GetAttributeSet();

	Cast<UTOHAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (ATOHPlayerController* PlayerController = Cast<ATOHPlayerController>(GetController()))
	{
		if (ATOHHUD* TOHHUD = Cast<ATOHHUD>(PlayerController->GetHUD()))
		{
			TOHHUD->InitOverlay(PlayerController, PState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}
