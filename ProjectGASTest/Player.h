#pragma once
#include "Character.h" // 부모 클래스 포함
#include "ItemBase.h" // 아이템 관련 클래스 포함
#include "Hit.h" // Hit 능력 관련 클래스 포함

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

    bool UseItem(int inventorySlot, Character& target, std::wstring& OutMessage) {
        if (inventorySlot < 0 || inventorySlot >= m_Inventory.size()) {
            OutMessage = L"잘못된 아이템 슬롯입니다."; // 실패 메시지도 설정
            return false;
        }

        auto itemToUse = m_Inventory[inventorySlot];
        if (itemToUse && itemToUse->UsageAbility) {
            // [수정] OutMessage를 그대로 전달하여 TryActivateAbility를 호출합니다.
            return GetAbilitySystemComponent()->TryActivateAbility(
                itemToUse->UsageAbility,
                target.GetAbilitySystemComponent(),
                OutMessage // 전달받은 OutMessage를 그대로 넘겨줌
            );
        }

        OutMessage = L"사용할 수 없는 아이템입니다."; // 실패 메시지도 설정
        return false;
    }
};