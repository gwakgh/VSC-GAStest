#include "Hit.h"
#include "AbilitySystemComponent.h" // ASC의 멤버 함수를 사용하기 위해 포함
#include "GameplayEffect.h"         // GameplayEffect 객체를 생성하기 위해 포함
#include "Character.h" // GetOwner() -> GetName() 때문에 필요
#include "ConsoleUtils.h" // GetRandomInt, GetRandomFloat 함수 사용을 위해 포함
#include "DamageUtils.h" // DamageUtils::CalculateDamage 함수를 사용하기 위해 포함

#include <string>
#include <iostream>

using namespace std;

// 생성자 구현: 스킬의 기본 정보를 설정합니다.
Hit::Hit() {
    // 스킬의 기본 정보 설정
    this->AbilityName = L"일반공격";
    this->ManaCost = 0.0f;
    this->DamageType = EDamageType::Physical;

    // 부모로부터 물려받은 'Activate' 변수에 람다 함수를 대입합니다.
    this->Activate = [this](AbilitySystemComponent* SourceASC, AbilitySystemComponent* TargetASC, wstring& OutMessage) {

        // 1. 명중률 계산
        auto sourceAttrs = SourceASC->GetAttributes();
        auto targetAttrs = TargetASC->GetAttributes();
        int hitChance = 95 + static_cast<int>(sourceAttrs->Agility - targetAttrs->Agility);

        // 2. 빗나감 판정
        if (ConsoleUtils::GetRandomInt(1, 100) > hitChance) {
            OutMessage = L"공격이 빗나갔다!";
            return true;
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
            1.5f, // 마법 multiplier (필요시 조정 가능)
            1.2f, // 물리 multiplier
            0.15f // 데미지 편차 15%
        );

        // 데미지 적용
        GameplayEffect damageEffect;
        damageEffect.AttributeToModify = "Health";
        damageEffect.ModifierValue = -finalDamage;
        TargetASC->ApplyGameplayEffectToSelf(damageEffect);

        OutMessage = TargetASC->GetOwner()->GetName() + L"에게 " + to_wstring(static_cast<int>(finalDamage)) + L"의 물리 데미지를 입혔다!";
		return true; // 스킬 사용 성공
        }; 
}
// 스킬 사용 가능 여부 확인 로직
bool Hit::CanActivate(AbilitySystemComponent* SourceASC) {
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