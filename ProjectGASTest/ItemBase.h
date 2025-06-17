#pragma once
#include <string>
#include <memory>

// ���� ����
class GameplayAbility;

// �������� ������ �����ϱ� ���� ������
enum class EItemType {
    Consumable, // �Ҹ�ǰ (���� ��)
    Equipment,  // ��� (��, ���� ��)
    Quest,      // ����Ʈ ������
    Etc         // ��Ÿ
};

class ItemBase {
public:
    std::string ItemName;
    std::string Description;
    EItemType Type;
    int MaxStack; // �ִ� �� ������ ��ĥ �� �ִ���

    // �� �������� ������� �� �ߵ��� �����Ƽ.
    // �� �����Ͱ� nullptr�̸� ����� �� ���� �������Դϴ�.
    std::shared_ptr<GameplayAbility> UsageAbility;

    ItemBase()
        : MaxStack(1), UsageAbility(nullptr) {
    }

    // ��� Ŭ�����̹Ƿ� ���� �Ҹ��ڴ� �ʼ��Դϴ�.
    virtual ~ItemBase() = default;
};