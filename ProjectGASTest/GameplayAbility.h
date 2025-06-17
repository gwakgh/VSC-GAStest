// GameplayAbility.h
#pragma once
#include <string>
#include <functional> // std::function을 사용하기 위해 추가

/*
*   GAS 의 UGameplayAbility 에 해당
*   캐릭터가 사용할 수 있는 능력(어빌리티)을 정의하는 클래스
*   혹은 스킬이나 행동에 대한 정의를 포함
*/

// 전방 선언
class AbilitySystemComponent;
class GameplayEffect;

enum class EDamageType {
    Physical, // 물리 피해
    Magical,  // 마법 피해
    True      // 고정 피해
};

class GameplayAbility {
public:
    std::wstring AbilityName = L"기본 공격";
    float ManaCost = 0.0f;
    float Cooldown = 0.0f;

	EDamageType DamageType = EDamageType::Physical; // 기본 피해 유형은 물리 피해

    GameplayAbility();
    // 이 어빌리티를 사용할 수 있는지 확인 (마나, 쿨타임 등)
    virtual bool CanActivate(AbilitySystemComponent* SourceASC);
    // 어빌리티를 실제로 발동시킴

    std::function<void(AbilitySystemComponent*, AbilitySystemComponent*, std::wstring&)> Activate;

    virtual ~GameplayAbility() = default; // 부모 클래스는 가상 소멸자를 갖는 것이 좋음
};