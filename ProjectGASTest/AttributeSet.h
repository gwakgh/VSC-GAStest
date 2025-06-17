// AttributeSet.h
#pragma once
/*
    GAS �� UAttributeSet �� �ش�
    ĳ������ ��� ��ġ�� �����ϴ� Ŭ����
*/
class AttributeSet {
public:
    // �⺻ �Ӽ�
    float Health = 100.0f;
    float MaxHealth = 100.0f;
    float Mana = 50.0f;
    float MaxMana = 50.0f;

    // ���� �Ӽ�
    float AttackPower = 10.0f;
    float DefensePower = 5.0f;

    // �Ӽ� ���濡 ���� ���� ó���� ���� �Լ� (���߿� Ȯ�� ����)
    // void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue);
    // void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data);
};