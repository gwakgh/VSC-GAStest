// GameplayEffect.h
#pragma once
#include <string>

/*
*   GAS�� UGameplayEffect�� �ش�
*   �����Ƽ�� �ߵ����� �� �߻��ϴ� ���� ȿ��(������, ġ��, ���� ��)�� �����ϴ� Ŭ����
*/

enum class EEffectType { Instant, Duration, Infinite };

class GameplayEffect {
public:
    EEffectType EffectType = EEffectType::Instant; // ���, ����, ����
    std::string AttributeToModify; // "Health", "DefensePower" ��
    float ModifierValue = 0.0f; // ������ �� (������ ����, ����� ����)
    float Duration = 0.0f; // ���� �ð� (���� ȿ���� ���)
};