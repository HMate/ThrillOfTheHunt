// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TOHProjectileSpell.h"

#include "Actor/TOHProjectile.h"
#include <Interaction/CombatInterface.h>

void UTOHProjectileSpell::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


}

void UTOHProjectileSpell::SpawnProjectile()
{
	auto* Avatar = GetAvatarActorFromActorInfo();
	const bool bIsServer = Avatar->HasAuthority();
	if (!bIsServer)
	{
		return;
	}

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Avatar);
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		// TODO: Set Projectile Rotation

		ATOHProjectile* Projectile = GetWorld()->SpawnActorDeferred<ATOHProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO: Give Projectile a Gameplay Effect Spec for causing damage.

		Projectile->FinishSpawning(SpawnTransform);
	}
}
