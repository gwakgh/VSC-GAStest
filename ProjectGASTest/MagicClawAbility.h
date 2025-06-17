#pragma once
#include "GameplayAbility.h"

class MagicClawAbility : public GameplayAbility {
public:
    // 생성자: 매직클로의 고유한 속성을 설정합니다.
    MagicClawAbility();

    // 부모의 가상 함수를 재정의하여 매직클로만의 로직을 구현합니다.
    // override 키워드는 부모의 함수를 재정의한다는 것을 명시하여 실수를 방지합니다.
    virtual bool CanActivate(AbilitySystemComponent* SourceASC) override;
};