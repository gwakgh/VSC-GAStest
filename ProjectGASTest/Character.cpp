#include "Character.h"
#include "AbilitySystemComponent.h" // ���⼭ AbilitySystemComponent�� ��ü ���Ǹ� ����

// ������ ����
Character::Character(std::string InName) : Name(InName) {
    ASC = std::make_unique<AbilitySystemComponent>(this);
}

// �Ҹ��� ���� (������ ����־ ��)
Character::~Character() {
}

// �ٸ� ��� �Լ����� ����
AbilitySystemComponent* Character::GetAbilitySystemComponent() const {
    return ASC.get();
}

const std::string& Character::GetName() const {
    return Name;
}