// Ronald Symon Frota e Frota All Rights Reserved

#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

// Chamado quando a habilidade é concedida ao AbilitySystemComponent.
void UWarriorGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	// Verifica se a política de ativação é ativar ao ser dada
	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		// Verifica se temos informação do ator e se a spec ainda não está ativa
		if (ActorInfo && !Spec.IsActive())
		{
			// Tenta ativar a habilidade usando o Handle da Spec
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

// Chamado para encerrar a habilidade.
void UWarriorGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	// Se a habilidade foi ativada quando foi dada, limpamos a referência/registro ao terminar
	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			// Remove a habilidade do AbilitySystemComponent usando o handle
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

// Retorna o componente de combate do Pawn associado ao avatar do ActorInfo.
UPawnCombatComponent* UWarriorGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	// Busca o componente do tipo UPawnCombatComponent no ator avatar
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

// Retorna o UWarriorAbilitySystemComponent a partir do CurrentActorInfo.
UWarriorAbilitySystemComponent* UWarriorGameplayAbility::GetWarriorAbilitySystemComponentFromActorInfo() const
{
	// Faz cast do AbilitySystemComponent atual para o tipo específico do projeto.
	return Cast<UWarriorAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
