#pragma once
#include "GameplayAbility.h"

class MagicClawAbility : public GameplayAbility {
public:
    // ������: ����Ŭ���� ������ �Ӽ��� �����մϴ�.
    MagicClawAbility();

    // �θ��� ���� �Լ��� �������Ͽ� ����Ŭ�θ��� ������ �����մϴ�.
    // override Ű����� �θ��� �Լ��� �������Ѵٴ� ���� ����Ͽ� �Ǽ��� �����մϴ�.
    virtual bool CanActivate(AbilitySystemComponent* SourceASC) override;
};