#pragma once
#include "ItemBase.h"
#include "GameplayAbility.h"    // 어빌리티를 생성하기 위해 필요
#include "GameplayEffect.h"     // 효과를 생성하기 위해 필요
#include "AbilitySystemComponent.h" // 어빌리티의 Activate 함수 인자로 필요
#include "Character.h"          // Character의 GetName()을 사용하기 위해 필요
#include <iostream>

// ItemBase를 상속받는 구체적인 아이템, HealthPotion
class HealthPotion : public ItemBase {
public:
    // HealthPotion 생성자
    HealthPotion() {
        // 1. 아이템 기본 정보 설정 (부모인 ItemBase로부터 물려받은 변수들)
        this->ItemName = "체력 포션";
        this->Description = "사용하면 체력을 50 회복합니다.";
        this->Type = EItemType::Consumable;
        this->MaxStack = 10; // 최대 10개까지 겹칠 수 있음

        // --- 2. 핵심 로직: '포션 사용' 어빌리티를 즉석에서 생성 ---

        // GameplayAbility의 기본 객체를 하나 생성합니다.
        auto PotionUsageAbility = std::make_shared<GameplayAbility>();
        PotionUsageAbility->AbilityName = "체력 포션 사용"; // 어빌리티의 이름

        // C++ 람다(Lambda)를 사용해 Activate 함수의 동작을 여기서 바로 정의합니다.
        // 이렇게 하면 PotionAbility.cpp 같은 별도 파일을 만들 필요가 없습니다.
        PotionUsageAbility->Activate = [this](AbilitySystemComponent* SourceASC, AbilitySystemComponent* TargetASC) {

            // 사용했을 때 콘솔에 메시지 출력
            // SourceASC->GetOwner()는 이 컴포넌트를 소유한 Character를 반환합니다.
            std::cout << SourceASC->GetOwner()->GetName() << "이(가) " << this->ItemName << "을(를) 사용합니다." << std::endl;

            // '체력 +50' 효과를 담은 GameplayEffect 객체를 생성합니다.
            GameplayEffect HealEffect;
            HealEffect.AttributeToModify = "Health";
            HealEffect.ModifierValue = 50.0f; // 50만큼 회복

            // 시전자(Source) 자신에게 효과를 적용합니다.
            SourceASC->ApplyGameplayEffectToSelf(HealEffect);

            // TODO: 실제 게임에서는 이 시점에 인벤토리에서 이 포션을 1개 제거하는 로직이 필요합니다.
            };

        // 3. 즉석에서 만든 어빌리티를 이 아이템의 '사용 효과'로 지정합니다.
        this->UsageAbility = PotionUsageAbility;
    }
};