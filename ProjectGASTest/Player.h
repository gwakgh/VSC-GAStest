#pragma once
#include "Character.h" // �θ� Ŭ���� ����
#include "ItemBase.h" // ������ ���� Ŭ���� ����
#include <iostream>
#include <vector>

class Player : public Character { // Character Ŭ������ public���� ���
private:
    int m_Level;
    int m_Experience;
    std::vector<std::shared_ptr<ItemBase>> m_Inventory;

public:
    // �����ڿ��� �θ� Ŭ������ �����ڸ� ȣ�� (�ſ� �߿�)
    Player(const std::string& InName)
        : Character(InName), m_Level(1), m_Experience(0) {
        // �÷��̾� ���� �� Ư���� �ʱ�ȭ�� �ʿ��ϸ� ���⿡ �ۼ�
    }

    void ShowStatus() const {
        AttributeSet* attrs = GetAbilitySystemComponent()->GetAttributes();
        std::cout << "--- " << GetName() << " ���� ---" << std::endl;
        std::cout << "  HP: " << attrs->Health << " / " << attrs->MaxHealth << std::endl;
        std::cout << "  MP: " << attrs->Mana << " / " << attrs->MaxMana << std::endl;
        std::cout << "--------------------" << std::endl;
    }

    void AddExperience(int Amount) {
        m_Experience += Amount;
        // ����ġ�� Ư�� ��ġ�� ������ �������ϴ� ���� ��
        std::cout << GetName() << "��(��) ����ġ " << Amount << "��(��) ȹ���߽��ϴ�." << std::endl;
    }
    
    void AddItem(std::shared_ptr<ItemBase> NewItem) {
        // �κ��丮�� ������ �߰� ����

        if (NewItem == nullptr) return; // ��ȿ���� ���� �������� �߰����� ����

        m_Inventory.push_back(NewItem);
        std::cout << GetName() << "��(��) " << NewItem->ItemName << "��(��) ȹ���߽��ϴ�." << std::endl;
    }
    
};