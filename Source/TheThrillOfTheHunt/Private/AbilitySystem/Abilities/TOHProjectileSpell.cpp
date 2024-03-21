// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TOHProjectileSpell.h"

#include "Actor/TOHProjectile.h"
#include <Interaction/CombatInterface.h>
#include <AbilitySystemComponent.h>
#include <AbilitySystemBlueprintLibrary.h>

void UTOHProjectileSpell::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UTOHProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
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
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.0f;

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		ATOHProjectile* Projectile = GetWorld()->SpawnActorDeferred<ATOHProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const UAbilitySystemComponent* SourceASC =
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle =
			SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
		Projectile->DamageEffectSpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
