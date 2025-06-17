#pragma once
#include "Character.h" // 부모 클래스 포함
#include "ItemBase.h" // 아이템 관련 클래스 포함
#include <iostream>
#include <vector>

class Player : public Character { // Character 클래스를 public으로 상속
private:
    int m_Level;
    int m_Experience;
    std::vector<std::shared_ptr<ItemBase>> m_Inventory;

public:
    // 생성자에서 부모 클래스의 생성자를 호출 (매우 중요)
    Player(const std::string& InName)
        : Character(InName), m_Level(1), m_Experience(0) {
        // 플레이어 생성 시 특별한 초기화가 필요하면 여기에 작성
    }

    void ShowStatus() const {
        AttributeSet* attrs = GetAbilitySystemComponent()->GetAttributes();
        std::cout << "--- " << GetName() << " 상태 ---" << std::endl;
        std::cout << "  HP: " << attrs->Health << " / " << attrs->MaxHealth << std::endl;
        std::cout << "  MP: " << attrs->Mana << " / " << attrs->MaxMana << std::endl;
        std::cout << "--------------------" << std::endl;
    }

    void AddExperience(int Amount) {
        m_Experience += Amount;
        // 경험치가 특정 수치를 넘으면 레벨업하는 로직 등
        std::cout << GetName() << "이(가) 경험치 " << Amount << "을(를) 획득했습니다." << std::endl;
    }
    
    void AddItem(std::shared_ptr<ItemBase> NewItem) {
        // 인벤토리에 아이템 추가 로직

        if (NewItem == nullptr) return; // 유효하지 않은 아이템은 추가하지 않음

        m_Inventory.push_back(NewItem);
        std::cout << GetName() << "이(가) " << NewItem->ItemName << "을(를) 획득했습니다." << std::endl;
    }
    
};