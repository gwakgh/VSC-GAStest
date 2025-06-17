#include "HealthPotion.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "Character.h"

HealthPotion::HealthPotion() {
    this->ItemName = L"ü�� ����";
    this->Description = L"����ϸ� ü���� 50 ȸ���մϴ�.";
    this->Type = EItemType::Consumable;
    this->MaxStack = 10;

    auto PotionUsageAbility = std::make_shared<GameplayAbility>();

    PotionUsageAbility->AbilityName = this->ItemName; 

    PotionUsageAbility->Activate = [this](AbilitySystemComponent* SourceASC, AbilitySystemComponent*, std::wstring& OutMessage) {
        GameplayEffect HealEffect;
        HealEffect.AttributeToModify = "Health"; // "Health"�� ���� Attribute �̸��� ��ġ�ؾ� �մϴ�.
        HealEffect.ModifierValue = 50.0f;

        SourceASC->ApplyGameplayEffectToSelf(HealEffect);

        // OutMessage�� ä���ݴϴ�. GetOwner()�� Character�� ��ȯ�Ѵٰ� �����մϴ�.
        OutMessage = SourceASC->GetOwner()->GetName() + L"��(��) " + this->ItemName + L"��(��) ����մϴ�.";

        // ������ ��� �� �κ��丮���� �����ϴ� ������ �ʿ��� �� �ֽ��ϴ�.
        //SourceASC->GetOwner()->GetInventory()->RemoveItem(this->ItemName, 1);

        return true; // ���� ���θ� ��ȯ�ϵ��� Activate �Լ��� �����ϸ� �� �����ϴ�.
        };

    this->UsageAbility = PotionUsageAbility;
}
