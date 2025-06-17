#include "GameplayAbility.h"

/*
*   GAS의 UGameplayAbility에 해당
*   해당 파일은 명목상으로만 존재하며, 실제 구현은 이 클래스에서 파생된 클래스에서 이루어짐
*   다만, 공통 로직을 생성할 경우 이곳에 작성할 수 있음 
*   - CC기 등으로 인해 모든 스킬 사용을 제한하고 싶은 경우
*   - 글로벌 쿨다운으로 스킬을 관리할 경우
*   - 디버깅을 위해 모든 스킬이 실행될 때 로그를 남기기 위한 경우 등
*/
// 생성자 구현
GameplayAbility::GameplayAbility() {
    // Activate 멤버 변수를 '아무것도 하지 않는' 기본 람다 함수로 초기화합니다.
    // 이렇게 하면 안정성이 높아집니다.
}

// CanActivate 함수의 실제 구현
bool GameplayAbility::CanActivate(AbilitySystemComponent* SourceASC) {
    // 지금은 기본 동작만 하지만, 나중에 공통 로직을 여기에 추가할 수 있음
    return true;
}
/*
void as() {
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

    // 4. 데미지 계산
    float baseDamage = 0.0f;
    float targetDefense = 0.0f;

    if (this->DamageType == EDamageType::Magical) {
        baseDamage = sourceAttrs->Intelligence * 1.5f;
        targetDefense = targetAttrs->MagicResistance;
    }
    else {
        baseDamage = sourceAttrs->Strength * 1.2f;
        targetDefense = targetAttrs->DefensePower;
    }

    float damageAfterDefense = max(1.0f, baseDamage - targetDefense);

    // 5. 최종 데미지에 난수 적용
    float minDamage = damageAfterDefense * 0.85f;
    float maxDamage = damageAfterDefense * 1.15f;
    float finalRandomDamage = ConsoleUtils::GetRandomFloat(minDamage, maxDamage);

    // 6. 최종 효과 적용 및 결과 메시지 설정
    GameplayEffect damageEffect;
    damageEffect.AttributeToModify = "Health";
    damageEffect.ModifierValue = -finalRandomDamage;
    TargetASC->ApplyGameplayEffectToSelf(damageEffect);
}
*/