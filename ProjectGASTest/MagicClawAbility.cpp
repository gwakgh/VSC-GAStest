#include "MagicClawAbility.h"
#include "AbilitySystemComponent.h" // ASC�� ��� �Լ��� ����ϱ� ���� ����
#include "GameplayEffect.h"         // GameplayEffect ��ü�� �����ϱ� ���� ����
#include "Character.h" // GetOwner() -> GetName() ������ �ʿ�
#include <iostream>

// ������ ����: ��ų�� �⺻ ������ �����մϴ�.
MagicClawAbility::MagicClawAbility() {
    // ��ų�� �⺻ ���� ����
    this->AbilityName = "����Ŭ��";
    this->ManaCost = 15.0f;
    this->Cooldown = 0.0f;

    // --- ���Ⱑ �ٽ� ---
    // �θ�κ��� �������� 'Activate' ������ ���� �Լ��� �����մϴ�.
    this->Activate = [this](AbilitySystemComponent* SourceASC, AbilitySystemComponent* TargetASC) {

        // ������ Activate �Լ��� �ִ� ������ �״�� ���⿡ �ۼ��մϴ�.

        // 1. �������� ���� �Ҹ�
        GameplayEffect ManaEffect;
        ManaEffect.AttributeToModify = "Mana";
        ManaEffect.ModifierValue = -this->ManaCost;
        SourceASC->ApplyGameplayEffectToSelf(ManaEffect);

        // 2. ��󿡰� ������ ����
        GameplayEffect DamageEffect;
        DamageEffect.AttributeToModify = "Health";
        // ������ ���: �������� �⺻ ���ݷ��� 120%
        float DamageToDeal = SourceASC->GetAttributes()->AttackPower * 1.2f;
        DamageEffect.ModifierValue = -DamageToDeal;
        TargetASC->ApplyGameplayEffectToSelf(DamageEffect);
        };
}
// ��ų ��� ���� ���� Ȯ�� ����
bool MagicClawAbility::CanActivate(AbilitySystemComponent* SourceASC) {
    // �������� �ɷ�ġ ������ �����ɴϴ�.
    AttributeSet* SourceAttributes = SourceASC->GetAttributes();

    // ������ ��ų ��뿡 �ʿ��� �������� ������ Ȯ���մϴ�.
    if (SourceAttributes->Mana < this->ManaCost) {
        // �� �޽����� main.cpp ���� �̹� ����ϹǷ� �ּ� ó���ϰų�, �� ���������� ���ܵ� �� �ֽ��ϴ�.
        // std::cout << "������ �����Ͽ� " << this->AbilityName << "��(��) ������ �� �����ϴ�." << std::endl;
        return false;
    }

    // ��� ������ ��������Ƿ� ��ų ����� �����մϴ�.
    return true;
}