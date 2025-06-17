#include "AbilitySystemComponent.h"
#include "Character.h" // Character 클래스의 정의를 포함
#include <iostream> // 콘솔 출력을 위해

// TryActivateAbility 함수의 구현
void AbilitySystemComponent::TryActivateAbility(const std::string& AbilityName, AbilitySystemComponent* TargetASC) {
    // 1. 부여된 어빌리티 목록에서 해당 이름의 어빌리티를 찾습니다.
    std::shared_ptr<GameplayAbility> FoundAbility = nullptr;
    for (const auto& ability : GrantedAbilities) {
        if (ability->AbilityName == AbilityName) {
            FoundAbility = ability;
            break;
        }
    }

    if (FoundAbility == nullptr) {
        std::cout << AbilityName << " 스킬을 배운 적이 없습니다." << std::endl;
        return;
    }

    // 2. 어빌리티를 사용할 수 있는지 확인합니다 (마나, 쿨타임 등).
    if (!FoundAbility->CanActivate(this)) {
        std::cout << AbilityName << " 스킬을 사용할 수 없습니다. (마나 부족 등)" << std::endl;
        return;
    }

    // 3. 어빌리티를 발동시킵니다.
    if (FoundAbility && FoundAbility->Activate) {
        std::cout << Owner->GetName() << "이(가) " << TargetASC->GetOwner()->GetName() << "에게 " << FoundAbility->AbilityName << " 시전!" << std::endl;
        FoundAbility->Activate(this, TargetASC);
    }
}


// ApplyGameplayEffectToSelf 함수의 구현
void AbilitySystemComponent::ApplyGameplayEffectToSelf(const GameplayEffect& Effect) {
    // 1. 어떤 속성을 변경할지 확인합니다.
    if (Effect.AttributeToModify == "Health") {
        BaseAttributes.Health += Effect.ModifierValue;

        // 체력이 최대 체력을 넘지 않도록 조정
        if (BaseAttributes.Health > BaseAttributes.MaxHealth) {
            BaseAttributes.Health = BaseAttributes.MaxHealth;
        }
        // 체력이 0 미만으로 내려가지 않도록 조정
        if (BaseAttributes.Health < 0) {
            BaseAttributes.Health = 0;
        }

        if (Effect.ModifierValue > 0) {
            std::cout << Owner->GetName() << "의 체력이 " << Effect.ModifierValue << "만큼 회복되었습니다. (현재 HP: " << BaseAttributes.Health << ")" << std::endl;
        }
        else {
            std::cout << Owner->GetName() << "이(가) " << -Effect.ModifierValue << "의 데미지를 입었습니다. (현재 HP: " << BaseAttributes.Health << ")" << std::endl;
        }
    }
    else if (Effect.AttributeToModify == "Mana") {
        // 마나 변경 로직...
    }
    // ... 다른 속성들에 대한 처리

    // TODO: 지속(Duration) 효과에 대한 처리는 나중에 구현
}