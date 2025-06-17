#include "AbilitySystemComponent.h"
#include "Character.h" // Character 클래스의 정의를 포함
#include <iostream> // 콘솔 출력을 위해

// 속성 변경 효과를 자기 자신에게 적용하는 함수
void AbilitySystemComponent::ApplyGameplayEffectToSelf(const GameplayEffect& Effect) {
    bool bRecalculate = false; // 재계산이 필요한지 여부를 기억할 변수

    if (Effect.AttributeToModify == "Health") {
        BaseAttributes.Health += Effect.ModifierValue;

        // 체력 상한/하한 조정
        if (BaseAttributes.Health > BaseAttributes.MaxHealth) {
            BaseAttributes.Health = BaseAttributes.MaxHealth;
        }
        if (BaseAttributes.Health < 0) {
            BaseAttributes.Health = 0;
        }
    }
    else if (Effect.AttributeToModify == "Mana") {
        BaseAttributes.Mana += Effect.ModifierValue;

        if (BaseAttributes.Mana > BaseAttributes.MaxMana) {
            BaseAttributes.Mana = BaseAttributes.MaxMana;
        }
        if (BaseAttributes.Mana < 0) {
            BaseAttributes.Mana = 0;
        }
    }
    else if (Effect.AttributeToModify == "DefensePower") {
        BaseAttributes.DefensePower += Effect.ModifierValue;
        if (BaseAttributes.DefensePower < 0) {
            BaseAttributes.DefensePower = 0;
        }
    }
    else if (Effect.AttributeToModify == "Strength") {
        BaseAttributes.Strength += Effect.ModifierValue;
        bRecalculate = true; // 힘이 바뀌었으니 재계산 필요
    }
    else if (Effect.AttributeToModify == "Intelligence") {
        BaseAttributes.Intelligence += Effect.ModifierValue;
        bRecalculate = true; // 지능이 바뀌었으니 재계산 필요
    }
    // [추가] 힘이나 지능이 변경되었다면, 파생 스탯을 다시 계산합니다.
    if (bRecalculate) {
        BaseAttributes.RecalculateDerivedStats();
    }
}

// [이름으로 어빌리티 찾아서 실행] 버전
bool AbilitySystemComponent::TryActivateAbility(const std::wstring& AbilityName, AbilitySystemComponent* TargetASC, std::wstring& OutMessage) {
    std::shared_ptr<GameplayAbility> FoundAbility = nullptr;
    for (const auto& ability : GrantedAbilities) {
        if (ability->AbilityName == AbilityName) {
            FoundAbility = ability;
            break;
        }
    }

    // 어빌리티를 직접 전달하는 아래의 오버로딩 함수를 재사용하여 중복을 줄입니다.
    return TryActivateAbility(FoundAbility, TargetASC, OutMessage);
}

// [어빌리티 객체를 직접 받아서 실행] 버전 (오버로딩)
bool AbilitySystemComponent::TryActivateAbility(std::shared_ptr<GameplayAbility> AbilityToActivate, AbilitySystemComponent* TargetASC, std::wstring& OutMessage) {
    // 1. 전달받은 어빌리티 포인터가 유효한지 확인합니다.
    if (!AbilityToActivate) {
        OutMessage = L"알 수 없는 스킬입니다.";
        return false;
    }

    // 2. 사용 조건을 확인합니다.
    if (!AbilityToActivate->CanActivate(this)) {
        // CanActivate 함수 내부에서 "마나 부족" 등의 메시지를 출력할 수 있습니다.
        OutMessage = L"스킬을 사용할 수 없습니다.";
        return false;
    }

    // 3. 실행 가능한 함수가 있는지 확인하고 발동시킵니다.
    if (AbilityToActivate->Activate) {
        // 이제 시전 메시지는 BattleManager가, 결과 메시지는 Activate 함수가 담당합니다.
        AbilityToActivate->Activate(this, TargetASC, OutMessage);
        return true; // 성공
    }

    return false; // 실패
}