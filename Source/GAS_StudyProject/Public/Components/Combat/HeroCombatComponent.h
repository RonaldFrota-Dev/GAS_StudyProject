// Ronald Symon Frota e Frota All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AWarriorHeroWeapon;
/**
 * 
 */
UCLASS()
class GAS_STUDYPROJECT_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Warrior | Combat")
	AWarriorHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
};
