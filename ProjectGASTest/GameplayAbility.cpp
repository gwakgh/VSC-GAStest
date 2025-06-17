#include "GameplayAbility.h"
#include "AbilitySystemComponent.h" // ASC의 멤버 함수를 사용하기 위해 포함
#include "ConsoleUtils.h" // ConsoleUtils::GetRandomInt, GetRandomFloat 사용을 위해 포함
#include "DamageUtils.h" // DamageUtils::CalculateDamage 사용을 위해 포함

/*
*   GAS의 UGameplayAbility에 해당
*   해당 파일은 명목상으로만 존재하며, 실제 구현은 이 클래스에서 파생된 클래스에서 이루어짐
*   다만, 공통 로직을 생성할 경우 이곳에 작성할 수 있음 
*   - CC기 등으로 인해 모든 스킬 사용을 제한하고 싶은 경우
*   - 글로벌 쿨다운으로 스킬을 관리할 경우
*   - 디버깅을 위해 모든 스킬이 실행될 때 로그를 남기기 위한 경우 등
*/
// 생성자 구현
GameplayAbility::GameplayAbility() {
    // Activate 멤버 변수를 '아무것도 하지 않는' 기본 람다 함수로 초기화합니다.
    // 이렇게 하면 안정성이 높아집니다.
}

// CanActivate 함수의 실제 구현
bool GameplayAbility::CanActivate(AbilitySystemComponent* SourceASC) {
    // 지금은 기본 동작만 하지만, 나중에 공통 로직을 여기에 추가할 수 있음
    return true;
}
float GameplayAbility::ComputeStandardDamage(
    AttributeSet* source, AttributeSet* target,
    float magMul, float physMul, float variance)
{
    return DamageUtils::CalculateDamage(source, target, this->DamageType, magMul, physMul, variance);
}