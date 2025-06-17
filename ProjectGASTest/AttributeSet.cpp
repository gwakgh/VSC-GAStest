#include "AttributeSet.h"
#include <algorithm> // std::min을 사용하기 위해

// 파생 스탯 (MaxHealth, MaxMana)을 다시 계산하는 함수
void AttributeSet::RecalculateDerivedStats() {
    // 힘 1당 최대 체력 3 증가
    MaxHealth = BaseMaxHealth + (Strength * 3.0f);

    // 지능 1당 최대 마나 5 증가
    MaxMana = BaseMaxMana + (Intelligence * 5.0f);

    // 재계산 후 현재 체력/마나가 최대치를 넘지 않도록 보정
    Health = std::min(Health, MaxHealth);
    Mana = std::min(Mana, MaxMana);
}