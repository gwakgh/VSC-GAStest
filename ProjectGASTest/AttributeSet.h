#pragma once

class AttributeSet {
public:
    // --- 직접 변하는 스탯 ---
    float Health = 100.0f;
    float Mana = 50.0f;

    // --- 기본 스탯 ---
    float Strength = 10.0f;
    float Intelligence = 10.0f;
    float Agility = 5.0f;

    // --- 방어 스탯 ---
    float DefensePower = 5.0f;
    float MagicResistance = 5.0f;

    // --- 파생 스탯 ---
    float BaseMaxHealth = 85.0f;
    float BaseMaxMana = 25.0f;
    float MaxHealth = 100.0f;
    float MaxMana = 50.0f;

    // [중요] 이 함수의 선언이 여기에 반드시 있어야 합니다.
    void RecalculateDerivedStats();
};