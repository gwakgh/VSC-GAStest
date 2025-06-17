#include "MagicClawAbility.h"
#include "AbilitySystemComponent.h" // ASC의 멤버 함수를 사용하기 위해 포함
#include "GameplayEffect.h"         // GameplayEffect 객체를 생성하기 위해 포함
#include "Character.h" // GetOwner() -> GetName() 때문에 필요
#include "ConsoleUtils.h" // ConsoleUtils::GetRandomInt, GetRandomFloat 사용을 위해 포함
#include "DamageUtils.h" // DamageUtils::CalculateDamage 사용을 위해 포함

#include <iostream>
#include <algorithm>

using namespace std;

MagicClawAbility::MagicClawAbility() {
    // --- 스킬의 기본 정보 설정 ---
    this->AbilityName = L"매직클로";
    this->ManaCost = 15.0f;
    this->DamageType = EDamageType::Magical;

    // --- [수정됨] 스킬의 실제 동작(Activate)을 하나의 람다 함수로 정의 ---
    this->Activate = [this](AbilitySystemComponent* SourceASC, AbilitySystemComponent* TargetASC, wstring& OutMessage) {

        // 1. 명중률 계산
        auto sourceAttrs = SourceASC->GetAttributes();
        auto targetAttrs = TargetASC->GetAttributes();
        int hitChance = 95 + static_cast<int>(sourceAttrs->Agility - targetAttrs->Agility);

        // 2. 빗나감 판정
        if (ConsoleUtils::GetRandomInt(1, 100) > hitChance) {
            OutMessage = L"공격이 빗나갔다!";
            return;
        }

        // 3. 마나 소모 (명중했을 때만)
        GameplayEffect manaEffect;
        manaEffect.AttributeToModify = "Mana";
        manaEffect.ModifierValue = -this->ManaCost;
        SourceASC->ApplyGameplayEffectToSelf(manaEffect);

        // DamageUtils를 활용한 데미지 계산
        float finalDamage = DamageUtils::CalculateDamage(
            sourceAttrs,
            targetAttrs,
            this->DamageType,
			2.5f, // AP 계수 (데미지 증가)
			1.2f, // AD 계수 (데미지 증가)
            0.15f // 데미지 편차 15%
        );

        // 데미지 적용
        GameplayEffect damageEffect;
        damageEffect.AttributeToModify = "Health";
        damageEffect.ModifierValue = -finalDamage;
        TargetASC->ApplyGameplayEffectToSelf(damageEffect);

        OutMessage = TargetASC->GetOwner()->GetName() + L"에게 " + to_wstring(static_cast<int>(finalDamage)) + L"의 마법 데미지를 입혔다!";
        }; // [수정됨] 람다 대입문이 끝났음을 알리는 세미콜론(;)을 반드시 추가해야 합니다.
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