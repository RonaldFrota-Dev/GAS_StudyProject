// Ronald Symon Frota e Frota All Rights Reserved

#include "Components/Combat/HeroCombatComponent.h"

#include "Itens/Weapons/WarriorHeroWeapon.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
