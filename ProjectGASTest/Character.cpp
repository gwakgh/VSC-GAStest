#include "Character.h"
#include "AbilitySystemComponent.h"

Character::Character(std::wstring InName) : Name(InName) {
    ASC = std::make_unique<AbilitySystemComponent>(this);
}

Character::~Character() {
}

AbilitySystemComponent* Character::GetAbilitySystemComponent() const {
    return ASC.get();
}

const std::wstring& Character::GetName() const {
    return Name;
}