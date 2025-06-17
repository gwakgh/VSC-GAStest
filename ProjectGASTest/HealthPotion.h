#pragma once
#include "ItemBase.h"
#include "GameplayAbility.h"    // 어빌리티를 생성하기 위해 필요
#include "GameplayEffect.h"     // 효과를 생성하기 위해 필요
#include "AbilitySystemComponent.h" // 어빌리티의 Activate 함수 인자로 필요
#include "Character.h"          // Character의 GetName()을 사용하기 위해 필요

#include <iostream>
#include <string>

using namespace std;

// ItemBase를 상속받는 구체적인 아이템, HealthPotion
class HealthPotion : public ItemBase {
public:
    // HealthPotion 생성자
    HealthPotion();
};