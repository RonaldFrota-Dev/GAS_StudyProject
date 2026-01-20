// Ronald Symon Frota e Frota All Rights Reserved

#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"

//Retorna o ponteiro para o AWarriorHeroCharacter a partir do CurrentActorInfo.
AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	// Se o CachedWarriorHeroCharacter não for válido, tenta realizar o cast de CurrentActorInfo->AvatarActor.
	if (!CachedWarriorHeroCharacter.IsValid())
	{
		CachedWarriorHeroCharacter = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	
	// Retorna CachedWarriorHeroCharacter, ou nullptr se não for válido.
	return CachedWarriorHeroCharacter.IsValid()? CachedWarriorHeroCharacter.Get() : nullptr;
}

// Retorna o ponteiro para o AWarriorHeroController a partir do CurrentActorInfo.
AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	// Se o cache não for válido, tenta realizar o cast de CurrentActorInfo->PlayerController.
	if (!CachedWarriorHeroController.IsValid())
	{
		CachedWarriorHeroController = Cast<AWarriorHeroController>(CurrentActorInfo->PlayerController);
	}

	// Retorna CachedWarriorHeroController, ou nullptr se não for válido.
	return CachedWarriorHeroController.IsValid()? CachedWarriorHeroController.Get() : nullptr;
}

/** 
 * Retorna o componente de combate do personagem (UHeroCombatComponent).
 * Observação importante: 
		GetHeroCharacterFromActorInfo() pode retornar nullptr.
		Para evitar crashes por desreferência de ponteiro nulo, checamos antes de chamar GetHeroCombatComponent().
**/
UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
