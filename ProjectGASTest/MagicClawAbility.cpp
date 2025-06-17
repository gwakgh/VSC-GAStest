#include "MagicClawAbility.h"
#include "AbilitySystemComponent.h" // ASC의 멤버 함수를 사용하기 위해 포함
#include "GameplayEffect.h"         // GameplayEffect 객체를 생성하기 위해 포함
#include "Character.h" // GetOwner() -> GetName() 때문에 필요
#include <iostream>

// 생성자 구현: 스킬의 기본 정보를 설정합니다.
MagicClawAbility::MagicClawAbility() {
    // 스킬의 기본 정보 설정
    this->AbilityName = "매직클로";
    this->ManaCost = 15.0f;
    this->Cooldown = 0.0f;

    // --- 여기가 핵심 ---
    // 부모로부터 물려받은 'Activate' 변수에 람다 함수를 대입합니다.
    this->Activate = [this](AbilitySystemComponent* SourceASC, AbilitySystemComponent* TargetASC) {

        // 이전에 Activate 함수에 있던 로직을 그대로 여기에 작성합니다.

        // 1. 시전자의 마나 소모
        GameplayEffect ManaEffect;
        ManaEffect.AttributeToModify = "Mana";
        ManaEffect.ModifierValue = -this->ManaCost;
        SourceASC->ApplyGameplayEffectToSelf(ManaEffect);

        // 2. 대상에게 데미지 적용
        GameplayEffect DamageEffect;
        DamageEffect.AttributeToModify = "Health";
        // 데미지 계산: 시전자의 기본 공격력의 120%
        float DamageToDeal = SourceASC->GetAttributes()->AttackPower * 1.2f;
        DamageEffect.ModifierValue = -DamageToDeal;
        TargetASC->ApplyGameplayEffectToSelf(DamageEffect);
        };
}
// 스킬 사용 가능 여부 확인 로직
bool MagicClawAbility::CanActivate(AbilitySystemComponent* SourceASC) {
    // 시전자의 능력치 정보를 가져옵니다.
    AttributeSet* SourceAttributes = SourceASC->GetAttributes();

    // 마나가 스킬 사용에 필요한 마나보다 적은지 확인합니다.
    if (SourceAttributes->Mana < this->ManaCost) {
        // 이 메시지는 main.cpp 에서 이미 출력하므로 주석 처리하거나, 상세 디버깅용으로 남겨둘 수 있습니다.
        // std::cout << "마나가 부족하여 " << this->AbilityName << "을(를) 시전할 수 없습니다." << std::endl;
        return false;
    }

    // 모든 조건을 통과했으므로 스킬 사용이 가능합니다.
    return true;
}