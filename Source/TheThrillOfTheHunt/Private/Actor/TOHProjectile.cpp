// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TOHProjectile.h"

#include <Components/SphereComponent.h>
#include <Components/AudioComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <NiagaraFunctionLibrary.h>
#include <TheThrillOfTheHunt/TheThrillOfTheHunt.h>
#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemComponent.h>

ATOHProjectile::ATOHProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void ATOHProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ATOHProjectile::OnSphereOverlap);

	TravelingSoundComponent = UGameplayStatics::SpawnSoundAttached(TravelingSound, GetRootComponent());
}

void ATOHProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		TravelingSoundComponent->Stop();
	}
	Super::Destroyed();
}

void ATOHProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	TravelingSoundComponent->Stop();

	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC =
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data);
		}

		Destroy();
	}
	else
	{
		bHit = true;
	}
}


