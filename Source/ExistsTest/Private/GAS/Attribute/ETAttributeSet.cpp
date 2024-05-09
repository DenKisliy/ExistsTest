// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/ETAttributeSet.h"

void UETAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UETAttributeSet, Health, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UETAttributeSet, MaxHealth, COND_OwnerOnly, REPNOTIFY_Always);
}

void UETAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetMaxHealthAttribute())
	{
		UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
		const float CurrentMaxValue = MaxHealth.GetCurrentValue();
		if (!FMath::IsNearlyEqual(CurrentMaxValue, NewValue) && AbilityComp)
		{
			const float CurrentValue = Health.GetCurrentValue();
			float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewValue / CurrentMaxValue) - CurrentValue : NewValue;

			AbilityComp->ApplyModToAttributeUnsafe(GetHealthAttribute(), EGameplayModOp::Additive, NewDelta);
		}
	}
}

void UETAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
}

void UETAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UETAttributeSet, Health, OldHealth);
}

void UETAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UETAttributeSet, MaxHealth, OldMaxHealth);
}