// DamageUtils.cpp
#include "DamageUtils.h"
#include "ConsoleUtils.h"
#include <algorithm>

float DamageUtils::CalculateDamage(
    const AttributeSet* source,
    const AttributeSet* target,
    EDamageType type,
    float magMul,
    float physMul,
    float variance)
{
    float base = 0, def = 0;
    if (type == EDamageType::Magical) {
        base = source->Intelligence * magMul;
        def = target->MagicResistance;
    }
    else {
        base = source->Strength * physMul;
        def = target->DefensePower;
    }

    float result = max(1.0f, base - def);
    float minDmg = result * (1 - variance);
    float maxDmg = result * (1 + variance);
    return ConsoleUtils::GetRandomFloat(minDmg, maxDmg);
}
