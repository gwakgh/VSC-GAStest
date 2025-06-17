// AbilitySystemComponent.h
#pragma once
#include <vector>
#include <memory>
#include "AttributeSet.h"
#include "GameplayAbility.h"
#include "GameplayEffect.h"

/*
*   GAS�� UAbilitySystemComponent�� �ش�
*   ��� ���� �Ѱ��ϴ� ��Ʈ�� Ÿ�� ������ �ϴ� Ŭ����
*   ĳ���ʹ� �� ������Ʈ�� �����ϸ� �����Ƽ �ο�, �ߵ�, ����Ʈ ���� ���� ��� �� Ŭ������ ���� ����
*/

class Character; // ���� ����

class AbilitySystemComponent {
private:
    AttributeSet BaseAttributes; // �⺻ �Ӽ�
    std::vector<std::shared_ptr<GameplayAbility>> GrantedAbilities;

public:
    Character* Owner; // �� ������Ʈ�� ������

    Character* GetOwner() const { return Owner; }

    AbilitySystemComponent(Character* InOwner) : Owner(InOwner) {}

    // �����Ƽ�� �ο�����
    void GrantAbility(std::shared_ptr<GameplayAbility> Ability) {
        GrantedAbilities.push_back(Ability);
    }

    // �����Ƽ ��� �õ�
    void TryActivateAbility(const std::string& AbilityName, AbilitySystemComponent* TargetASC);

    // �ڽſ��� �����÷��� ����Ʈ�� ����
    void ApplyGameplayEffectToSelf(const GameplayEffect& Effect);

    // AttributeSet�� ���� �����ϱ� ���� Getter
    AttributeSet* GetAttributes() { return &BaseAttributes; }
};