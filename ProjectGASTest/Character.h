// Character.h
#pragma once
#include <string>
#include <memory>
#include "AbilitySystemComponent.h"

/*
*   Unreal Engine�� ACharacter�� �ش�
*   ĳ���� Ȥ�� ���� ���� �⺻ Ŭ����, �̸��� AbilitySystemComponent�� ����
*/

class Character {
protected:
    std::string Name;
    std::unique_ptr<AbilitySystemComponent> ASC;

public:
    Character(std::string InName);

    virtual ~Character();

    AbilitySystemComponent* GetAbilitySystemComponent() const;

    const std::string& GetName() const;
};