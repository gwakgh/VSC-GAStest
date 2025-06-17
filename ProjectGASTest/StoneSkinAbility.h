#pragma once
#include "GameplayAbility.h"

class StoneSkinAbility : public GameplayAbility {
public:
    StoneSkinAbility();
    virtual bool CanActivate(AbilitySystemComponent* SourceASC) override;
};
