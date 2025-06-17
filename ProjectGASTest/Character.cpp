#include "Character.h"
#include "AbilitySystemComponent.h" // 여기서 AbilitySystemComponent의 전체 정의를 포함

// 생성자 구현
Character::Character(std::string InName) : Name(InName) {
    ASC = std::make_unique<AbilitySystemComponent>(this);
}

// 소멸자 구현 (지금은 비어있어도 됨)
Character::~Character() {
}

// 다른 멤버 함수들의 구현
AbilitySystemComponent* Character::GetAbilitySystemComponent() const {
    return ASC.get();
}

const std::string& Character::GetName() const {
    return Name;
}