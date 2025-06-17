// GameplayAbility.h
#pragma once
#include <string>
#include <functional> // std::function�� ����ϱ� ���� �߰�

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

    GameplayAbility();
    // �� �����Ƽ�� ����� �� �ִ��� Ȯ�� (����, ��Ÿ�� ��)
    virtual bool CanActivate(AbilitySystemComponent* SourceASC);
    // �����Ƽ�� ������ �ߵ���Ŵ
    std::function<void(AbilitySystemComponent*, AbilitySystemComponent*)> Activate;


    virtual ~GameplayAbility() = default; // �θ� Ŭ������ ���� �Ҹ��ڸ� ���� ���� ����
};