#include "GameplayAbility.h"

/*
*   GAS�� UGameplayAbility�� �ش�
*   �ش� ������ �������θ� �����ϸ�, ���� ������ �� Ŭ�������� �Ļ��� Ŭ�������� �̷����
*   �ٸ�, ���� ������ ������ ��� �̰��� �ۼ��� �� ���� 
*   - CC�� ������ ���� ��� ��ų ����� �����ϰ� ���� ���
*   - �۷ι� ��ٿ����� ��ų�� ������ ���
*   - ������� ���� ��� ��ų�� ����� �� �α׸� ����� ���� ��� ��
*/

// CanActivate �Լ��� ���� ����
bool GameplayAbility::CanActivate(AbilitySystemComponent* SourceASC) {
    // ������ �⺻ ���۸� ������, ���߿� ���� ������ ���⿡ �߰��� �� ����
    return true;
}

// Activate �Լ��� ���� ����
void GameplayAbility::Activate(AbilitySystemComponent* SourceASC, AbilitySystemComponent* TargetASC) {
    // �⺻ �ൿ�� �ƹ��͵� ���� ����
}