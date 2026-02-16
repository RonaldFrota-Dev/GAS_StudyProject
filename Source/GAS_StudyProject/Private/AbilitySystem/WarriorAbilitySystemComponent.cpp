// Ronald Symon Frota e Frota All Rights Reserved

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

// Chamado quando uma entrada de habilidade é pressionada (recebe uma tag de input)
// - Verifica se a tag de entrada é válida antes de processar.
// - Itera sobre as abilities ativáveis e tenta ativar aquelas cuja tag dinâmica
//   corresponde exatamente à tag recebida.
void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	// Se a tag não for válida, não faz nada
	if (!InInputTag.IsValid())
	{
		return;
	}
	
	// Percorre todas as abilities que podem ser ativadas neste ASC
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// Se a spec não contém a tag exata, pula para a próxima
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;
		
		// Tenta ativar a habilidade usando o handle da spec
		TryActivateAbility(AbilitySpec.Handle);
	}
}

// Chamado quando a entrada de habilidade é liberada.
void UWarriorAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}


// Concede um conjunto de abilities relacionadas a armas do herói.
// - Recebe um array de conjuntos de abilities \(`InDefaultWeaponAbilities`\), o nível aplicado e um array de saída para coletar os handles das specs concedidas.
// - Para cada conjunto válido, cria uma FGameplayAbilitySpec, define propriedades (SourceObject, Level, Tag dinâmica) e chama GiveAbility. Armazena o handle retornado em `OutGrantedAbilitySpecHandles`.
void UWarriorAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}
	
	for (const FWarriorHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		// Ignora conjuntos inválidos
		if (!AbilitySet.IsValid()) continue;
		
		// Cria a spec da ability a partir da classe/factory contida no AbilitySet
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UWarriorAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty())
	{
		return;
	}
	
	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}
	
	InSpecHandlesToRemove.Empty();
}

bool UWarriorAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());
	
	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];
		
		check(SpecToActivate);

		if (!SpecToActivate->IsActive())
		{
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}
	
	return false;
}

