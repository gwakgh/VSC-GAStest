#pragma once
#include "GameplayAbility.h"

class Hit : public GameplayAbility {
public:
    // ������: ����Ŭ���� ������ �Ӽ��� �����մϴ�.
    Hit();

    // �θ��� ���� �Լ��� �������Ͽ� ����Ŭ�θ��� ������ �����մϴ�.
    // override Ű����� �θ��� �Լ��� �������Ѵٴ� ���� ����Ͽ� �Ǽ��� �����մϴ�.
    virtual bool CanActivate(AbilitySystemComponent* SourceASC) override;
};