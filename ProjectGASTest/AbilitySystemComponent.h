// AbilitySystemComponent.h
#pragma once
#include <vector>
#include <string>
#include <memory>
#include "AttributeSet.h"
#include "GameplayAbility.h"
#include "GameplayEffect.h"

/*
*   GAS의 UAbilitySystemComponent에 해당
*   모든 것을 총괄하는 컨트롤 타워 역할을 하는 클래스
*   캐릭터는 이 컴포넌트를 소유하며 어빌리티 부여, 발동, 이펙트 적용 등을 모두 이 클래스를 통해 수행
*/

class Character; // 전방 선언

class AbilitySystemComponent {
private:
    AttributeSet BaseAttributes; // 기본 속성
    std::vector<std::shared_ptr<GameplayAbility>> GrantedAbilities;

public:
    Character* Owner; // 이 컴포넌트의 소유자

    Character* GetOwner() const { return Owner; }

    AbilitySystemComponent(Character* InOwner) : Owner(InOwner) {}

    // 어빌리티를 부여받음
    void GrantAbility(std::shared_ptr<GameplayAbility> Ability) {
        GrantedAbilities.push_back(Ability);
    }

    // 어빌리티 사용 시도
    bool TryActivateAbility(const std::wstring& AbilityName, AbilitySystemComponent* TargetASC, std::wstring& OutMessage);
    bool TryActivateAbility(std::shared_ptr<GameplayAbility> AbilityToActivate, AbilitySystemComponent* TargetASC, std::wstring& OutMessage);
    //

    // 자신에게 게임플레이 이펙트를 적용
    void ApplyGameplayEffectToSelf(const GameplayEffect& Effect);

    // AttributeSet에 직접 접근하기 위한 Getter
    AttributeSet* GetAttributes() { return &BaseAttributes; }

    //부여된 어빌리티 목록을 외부에서 읽을 수 있는 Getter
    const std::vector<std::shared_ptr<GameplayAbility>>& GetGrantedAbilities() const {
        return GrantedAbilities;
    }
};