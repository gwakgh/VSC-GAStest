#pragma once
#include <string>
#include <memory>

// 전방 선언
class GameplayAbility;

// 아이템의 종류를 구분하기 위한 열거형
enum class EItemType {
    Consumable, // 소모품 (포션 등)
    Equipment,  // 장비 (검, 갑옷 등)
    Quest,      // 퀘스트 아이템
    Etc         // 기타
};

class ItemBase {
public:
    std::string ItemName;
    std::string Description;
    EItemType Type;
    int MaxStack; // 최대 몇 개까지 겹칠 수 있는지

    // 이 아이템을 사용했을 때 발동될 어빌리티.
    // 이 포인터가 nullptr이면 사용할 수 없는 아이템입니다.
    std::shared_ptr<GameplayAbility> UsageAbility;

    ItemBase()
        : MaxStack(1), UsageAbility(nullptr) {
    }

    // 기반 클래스이므로 가상 소멸자는 필수입니다.
    virtual ~ItemBase() = default;
};