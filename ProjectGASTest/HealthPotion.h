#pragma once
#include "ItemBase.h"
#include "GameplayAbility.h"    // �����Ƽ�� �����ϱ� ���� �ʿ�
#include "GameplayEffect.h"     // ȿ���� �����ϱ� ���� �ʿ�
#include "AbilitySystemComponent.h" // �����Ƽ�� Activate �Լ� ���ڷ� �ʿ�
#include "Character.h"          // Character�� GetName()�� ����ϱ� ���� �ʿ�
#include <iostream>

// ItemBase�� ��ӹ޴� ��ü���� ������, HealthPotion
class HealthPotion : public ItemBase {
public:
    // HealthPotion ������
    HealthPotion() {
        // 1. ������ �⺻ ���� ���� (�θ��� ItemBase�κ��� �������� ������)
        this->ItemName = "ü�� ����";
        this->Description = "����ϸ� ü���� 50 ȸ���մϴ�.";
        this->Type = EItemType::Consumable;
        this->MaxStack = 10; // �ִ� 10������ ��ĥ �� ����

        // --- 2. �ٽ� ����: '���� ���' �����Ƽ�� �Ｎ���� ���� ---

        // GameplayAbility�� �⺻ ��ü�� �ϳ� �����մϴ�.
        auto PotionUsageAbility = std::make_shared<GameplayAbility>();
        PotionUsageAbility->AbilityName = "ü�� ���� ���"; // �����Ƽ�� �̸�

        // C++ ����(Lambda)�� ����� Activate �Լ��� ������ ���⼭ �ٷ� �����մϴ�.
        // �̷��� �ϸ� PotionAbility.cpp ���� ���� ������ ���� �ʿ䰡 �����ϴ�.
        PotionUsageAbility->Activate = [this](AbilitySystemComponent* SourceASC, AbilitySystemComponent* TargetASC) {

            // ������� �� �ֿܼ� �޽��� ���
            // SourceASC->GetOwner()�� �� ������Ʈ�� ������ Character�� ��ȯ�մϴ�.
            std::cout << SourceASC->GetOwner()->GetName() << "��(��) " << this->ItemName << "��(��) ����մϴ�." << std::endl;

            // 'ü�� +50' ȿ���� ���� GameplayEffect ��ü�� �����մϴ�.
            GameplayEffect HealEffect;
            HealEffect.AttributeToModify = "Health";
            HealEffect.ModifierValue = 50.0f; // 50��ŭ ȸ��

            // ������(Source) �ڽſ��� ȿ���� �����մϴ�.
            SourceASC->ApplyGameplayEffectToSelf(HealEffect);

            // TODO: ���� ���ӿ����� �� ������ �κ��丮���� �� ������ 1�� �����ϴ� ������ �ʿ��մϴ�.
            };

        // 3. �Ｎ���� ���� �����Ƽ�� �� �������� '��� ȿ��'�� �����մϴ�.
        this->UsageAbility = PotionUsageAbility;
    }
};