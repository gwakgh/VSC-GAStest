#include "HealthPotion.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "Character.h"

HealthPotion::HealthPotion() {
    this->ItemName = L"체력 포션";
    this->Description = L"사용하면 체력을 50 회복합니다.";
    this->Type = EItemType::Consumable;
    this->MaxStack = 10;

    auto PotionUsageAbility = std::make_shared<GameplayAbility>();

    PotionUsageAbility->AbilityName = this->ItemName; 

    PotionUsageAbility->Activate = [this](AbilitySystemComponent* SourceASC, AbilitySystemComponent*, std::wstring& OutMessage) {
        GameplayEffect HealEffect;
        HealEffect.AttributeToModify = "Health"; // "Health"는 실제 Attribute 이름과 일치해야 합니다.
        HealEffect.ModifierValue = 50.0f;

        SourceASC->ApplyGameplayEffectToSelf(HealEffect);

        // OutMessage를 채워줍니다. GetOwner()가 Character를 반환한다고 가정합니다.
        OutMessage = SourceASC->GetOwner()->GetName() + L"이(가) " + this->ItemName + L"을(를) 사용합니다.";

        // 아이템 사용 후 인벤토리에서 제거하는 로직이 필요할 수 있습니다.
        //SourceASC->GetOwner()->GetInventory()->RemoveItem(this->ItemName, 1);

        return true; // 성공 여부를 반환하도록 Activate 함수를 수정하면 더 좋습니다.
        };

    this->UsageAbility = PotionUsageAbility;
}
