// DamageUtils.h
#pragma once
#include "AttributeSet.h"
#include "GameplayAbility.h"

class DamageUtils {
public:
    static float CalculateDamage(
        const AttributeSet* sourceAttrs,
        const AttributeSet* targetAttrs,
        EDamageType type,
        float magMultiplier = 1.5f,
        float physMultiplier = 1.2f,
        float variance = 0.15f // 15% º¯µ¿Æø
    );
};
