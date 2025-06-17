#include "AbilitySystemComponent.h"
#include "Character.h" // Character Ŭ������ ���Ǹ� ����
#include <iostream> // �ܼ� ����� ����

// TryActivateAbility �Լ��� ����
void AbilitySystemComponent::TryActivateAbility(const std::string& AbilityName, AbilitySystemComponent* TargetASC) {
    // 1. �ο��� �����Ƽ ��Ͽ��� �ش� �̸��� �����Ƽ�� ã���ϴ�.
    std::shared_ptr<GameplayAbility> FoundAbility = nullptr;
    for (const auto& ability : GrantedAbilities) {
        if (ability->AbilityName == AbilityName) {
            FoundAbility = ability;
            break;
        }
    }

    if (FoundAbility == nullptr) {
        std::cout << AbilityName << " ��ų�� ��� ���� �����ϴ�." << std::endl;
        return;
    }

    // 2. �����Ƽ�� ����� �� �ִ��� Ȯ���մϴ� (����, ��Ÿ�� ��).
    if (!FoundAbility->CanActivate(this)) {
        std::cout << AbilityName << " ��ų�� ����� �� �����ϴ�. (���� ���� ��)" << std::endl;
        return;
    }

    // 3. �����Ƽ�� �ߵ���ŵ�ϴ�.
    if (FoundAbility && FoundAbility->Activate) {
        std::cout << Owner->GetName() << "��(��) " << TargetASC->GetOwner()->GetName() << "���� " << FoundAbility->AbilityName << " ����!" << std::endl;
        FoundAbility->Activate(this, TargetASC);
    }
}


// ApplyGameplayEffectToSelf �Լ��� ����
void AbilitySystemComponent::ApplyGameplayEffectToSelf(const GameplayEffect& Effect) {
    // 1. � �Ӽ��� �������� Ȯ���մϴ�.
    if (Effect.AttributeToModify == "Health") {
        BaseAttributes.Health += Effect.ModifierValue;

        // ü���� �ִ� ü���� ���� �ʵ��� ����
        if (BaseAttributes.Health > BaseAttributes.MaxHealth) {
            BaseAttributes.Health = BaseAttributes.MaxHealth;
        }
        // ü���� 0 �̸����� �������� �ʵ��� ����
        if (BaseAttributes.Health < 0) {
            BaseAttributes.Health = 0;
        }

        if (Effect.ModifierValue > 0) {
            std::cout << Owner->GetName() << "�� ü���� " << Effect.ModifierValue << "��ŭ ȸ���Ǿ����ϴ�. (���� HP: " << BaseAttributes.Health << ")" << std::endl;
        }
        else {
            std::cout << Owner->GetName() << "��(��) " << -Effect.ModifierValue << "�� �������� �Ծ����ϴ�. (���� HP: " << BaseAttributes.Health << ")" << std::endl;
        }
    }
    else if (Effect.AttributeToModify == "Mana") {
        // ���� ���� ����...
    }
    // ... �ٸ� �Ӽ��鿡 ���� ó��

    // TODO: ����(Duration) ȿ���� ���� ó���� ���߿� ����
}