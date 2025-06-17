#pragma once
#include "Character.h" // 부모 클래스 포함
#include "ItemBase.h" // 아이템 관련 클래스 포함
#include "Hit.h" // Hit 능력 관련 클래스 포함
#include "StoneSkinAbility.h"
#include "HealthPotion.h" // HealthPotion 아이템 관련 클래스 포함

#include <iostream>
#include <vector>
#include <memory>

class Player : public Character { // Character 클래스를 public으로 상속
private:
    int m_Level;
    int m_Experience;
    std::vector<std::shared_ptr<ItemBase>> m_Inventory;

public:
    // 생성자에서 부모 클래스의 생성자를 호출 (매우 중요)
    Player(const std::wstring& InName)
        : Character(InName), m_Level(1), m_Experience(0) {

        // 플레이어의 초기 스탯 설정 (필요 시)
        auto attrs = GetAbilitySystemComponent()->GetAttributes();
        attrs->Strength = 12.0f;
        attrs->Intelligence = 8.0f;

        // [추가] 설정된 초기 스탯을 바탕으로 파생 스탯을 계산
        attrs->RecalculateDerivedStats();
        // 현재 체력/마나도 최대치로 설정
        attrs->Health = attrs->MaxHealth;
        attrs->Mana = attrs->MaxMana;

        auto hit = std::make_shared<Hit>();
        this->GetAbilitySystemComponent()->GrantAbility(hit);
		auto stoneSkin = std::make_shared<StoneSkinAbility>();
        this->GetAbilitySystemComponent()->GrantAbility(stoneSkin);

        auto healthPotion = std::make_shared<HealthPotion>();
		AddItem(healthPotion);

    }

    void ShowStatus() const {
        AttributeSet* attrs = GetAbilitySystemComponent()->GetAttributes();
        std::wcout << L"--- " << GetName() << L" 상태 ---" << std::endl;
        std::wcout << L"  HP: " << attrs->Health << L" / " << attrs->MaxHealth << std::endl;
        std::wcout << L"  MP: " << attrs->Mana << L" / " << attrs->MaxMana << std::endl;
        std::wcout << L"--------------------" << std::endl;
    }

    void AddExperience(int Amount) {
        m_Experience += Amount;
        // 경험치가 특정 수치를 넘으면 레벨업하는 로직 등
        std::wcout << GetName().c_str() << L"이(가) 경험치 " << Amount << L"을(를) 획득했습니다." << std::endl;
    }

    void AddItem(std::shared_ptr<ItemBase> NewItem) {
        // 인벤토리에 아이템 추가 로직

        if (NewItem == nullptr) return; // 유효하지 않은 아이템은 추가하지 않음

        m_Inventory.push_back(NewItem);
        std::wcout << GetName().c_str() << L"이(가) " << NewItem->ItemName.c_str() << L"을(를) 획득했습니다." << std::endl;
    }
    const std::vector<std::shared_ptr<ItemBase>>& GetInventory() const {
        return m_Inventory;
    }
    std::vector<std::shared_ptr<ItemBase>> GetInventory() {
        return m_Inventory;
	}
};