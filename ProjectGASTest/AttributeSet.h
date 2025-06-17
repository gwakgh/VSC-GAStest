// AttributeSet.h
#pragma once
/*
    GAS 의 UAttributeSet 에 해당
    캐릭터의 모든 수치를 관리하는 클래스
*/
class AttributeSet {
public:
    // 기본 속성
    float Health = 100.0f;
    float MaxHealth = 100.0f;
    float Mana = 50.0f;
    float MaxMana = 50.0f;

    // 전투 속성
    float AttackPower = 10.0f;
    float DefensePower = 5.0f;

    // 속성 변경에 대한 전후 처리를 위한 함수 (나중에 확장 가능)
    // void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue);
    // void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data);
};