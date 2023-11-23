

#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Interaction/CombatInterface.h"
#include "Actor/AuraProjectile.h"

void UAuraProjectileSpell::ActivateAbility(
	const FGameplayAbilitySpecHandle	 Handle,
	const FGameplayAbilityActorInfo*	 ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData*			 TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)
		return;

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		// TODO: Set rotation

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO: Give the projectile a GE spec for causing damage

		Projectile->FinishSpawning(SpawnTransform);
	}
}