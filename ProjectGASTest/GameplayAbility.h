// GameplayAbility.h
#pragma once
#include <string>

/*
*   GAS 의 UGameplayAbility 에 해당
*   캐릭터가 사용할 수 있는 능력(어빌리티)을 정의하는 클래스
*   혹은 스킬이나 행동에 대한 정의를 포함
*/

// 전방 선언
class AbilitySystemComponent;
class GameplayEffect;

class GameplayAbility {
public:
    std::string AbilityName = "기본 공격";
    float ManaCost = 0.0f;
    float Cooldown = 0.0f;

    // 이 어빌리티를 사용할 수 있는지 확인 (마나, 쿨타임 등)
    virtual bool CanActivate(AbilitySystemComponent* SourceASC);
    // 어빌리티를 실제로 발동시킴
    virtual void Activate(AbilitySystemComponent* SourceASC, AbilitySystemComponent* TargetASC);

    virtual ~GameplayAbility() = default; // 부모 클래스는 가상 소멸자를 갖는 것이 좋음
};