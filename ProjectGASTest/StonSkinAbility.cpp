#include "StoneSkinAbility.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Character.h"

StoneSkinAbility::StoneSkinAbility() {
    this->AbilityName = L"���潺Ų";
    this->ManaCost = 10.0f;

    this->Activate = [this](AbilitySystemComponent* SourceASC, AbilitySystemComponent* /*TargetASC*/, std::wstring& OutMessage) {
        auto attrs = SourceASC->GetAttributes();

        GameplayEffect defBuff;
        defBuff.AttributeToModify = "DefensePower";
        defBuff.ModifierValue = +10.0f; // ���� +10
        
        //���� �Ҹ�
        GameplayEffect manaEffect;
        manaEffect.AttributeToModify = "Mana";
        manaEffect.ModifierValue = -this->ManaCost;
        SourceASC->ApplyGameplayEffectToSelf(manaEffect);

        SourceASC->ApplyGameplayEffectToSelf(defBuff);

        OutMessage = SourceASC->GetOwner()->GetName() + L"�� ������ �����ߴ�!";
        };
}

bool StoneSkinAbility::CanActivate(AbilitySystemComponent* SourceASC) {
    return SourceASC->GetAttributes()->Mana >= this->ManaCost;
}
