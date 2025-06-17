#pragma once
#include "Character.h" // �θ� Ŭ���� ����

class Monster : public Character {
public:
    // ������: �̸��� �Բ� �ʱ� ü��, ���ݷ��� �޾Ƽ� �����մϴ�.
    Monster(const std::string& InName, float InitialHealth, float InitialAttack)
        : Character(InName) // �θ� Ŭ����(Character)�� �����ڸ� ���� ȣ���մϴ�.
    {
        // �θ�κ��� �������� AbilitySystemComponent�� ���� �Ӽ�(AttributeSet)�� �����մϴ�.
        AttributeSet* MyAttributes = GetAbilitySystemComponent()->GetAttributes();

        // ������ �ɷ�ġ�� �����մϴ�.
        MyAttributes->MaxHealth = InitialHealth;
        MyAttributes->Health = InitialHealth;
        MyAttributes->AttackPower = InitialAttack;
    }

    // ���ʹ� �÷��̾�� �޸� ������ ���� ����� ������ �����Ƿ�
    // �� �ܿ� �߰����� �ڵ�� �ʿ� �����ϴ�.
    // ���߿� LootTable(����ǰ ���) ���� ���� �� Ŭ������ �߰��� �� �ֽ��ϴ�.
};