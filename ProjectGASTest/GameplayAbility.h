// GameplayAbility.h
#pragma once
#include <string>

/*
*   GAS �� UGameplayAbility �� �ش�
*   ĳ���Ͱ� ����� �� �ִ� �ɷ�(�����Ƽ)�� �����ϴ� Ŭ����
*   Ȥ�� ��ų�̳� �ൿ�� ���� ���Ǹ� ����
*/

// ���� ����
class AbilitySystemComponent;
class GameplayEffect;

class GameplayAbility {
public:
    std::string AbilityName = "�⺻ ����";
    float ManaCost = 0.0f;
    float Cooldown = 0.0f;

    // �� �����Ƽ�� ����� �� �ִ��� Ȯ�� (����, ��Ÿ�� ��)
    virtual bool CanActivate(AbilitySystemComponent* SourceASC);
    // �����Ƽ�� ������ �ߵ���Ŵ
    virtual void Activate(AbilitySystemComponent* SourceASC, AbilitySystemComponent* TargetASC);

    virtual ~GameplayAbility() = default; // �θ� Ŭ������ ���� �Ҹ��ڸ� ���� ���� ����
};