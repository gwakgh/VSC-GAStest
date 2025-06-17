#pragma once
#include "Character.h" // 부모 클래스 포함

class Monster : public Character {
public:
    // 생성자: 이름과 함께 초기 체력, 공격력을 받아서 설정합니다.
    Monster(const std::string& InName, float InitialHealth, float InitialAttack)
        : Character(InName) // 부모 클래스(Character)의 생성자를 먼저 호출합니다.
    {
        // 부모로부터 물려받은 AbilitySystemComponent를 통해 속성(AttributeSet)에 접근합니다.
        AttributeSet* MyAttributes = GetAbilitySystemComponent()->GetAttributes();

        // 몬스터의 능력치를 설정합니다.
        MyAttributes->MaxHealth = InitialHealth;
        MyAttributes->Health = InitialHealth;
        MyAttributes->AttackPower = InitialAttack;
    }

    // 몬스터는 플레이어와 달리 별도의 고유 기능이 지금은 없으므로
    // 이 외에 추가적인 코드는 필요 없습니다.
    // 나중에 LootTable(전리품 목록) 같은 것을 이 클래스에 추가할 수 있습니다.
};