// Character.h
#pragma once
#include <string>
#include <memory>
#include "AbilitySystemComponent.h"

/*
*   Unreal Engine의 ACharacter에 해당
*   캐릭터 혹은 몬스터 등의 기본 클래스, 이름과 AbilitySystemComponent를 포함
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