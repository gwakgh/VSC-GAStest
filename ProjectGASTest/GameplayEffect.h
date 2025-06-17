// GameplayEffect.h
#pragma once
#include <string>

/*
*   GAS의 UGameplayEffect에 해당
*   어빌리티가 발동했을 때 발생하는 실제 효과(데미지, 치유, 버프 등)를 정의하는 클래스
*/

enum class EEffectType { Instant, Duration, Infinite };

class GameplayEffect {
public:
    EEffectType EffectType = EEffectType::Instant; // 즉시, 지속, 무한
    std::string AttributeToModify; // "Health", "DefensePower" 등
    float ModifierValue = 0.0f; // 변경할 값 (음수면 감소, 양수면 증가)
    float Duration = 0.0f; // 지속 시간 (지속 효과일 경우)
};