#include "GameplayAbility.h"

/*
*   GAS�� UGameplayAbility�� �ش�
*   �ش� ������ �������θ� �����ϸ�, ���� ������ �� Ŭ�������� �Ļ��� Ŭ�������� �̷����
*   �ٸ�, ���� ������ ������ ��� �̰��� �ۼ��� �� ���� 
*   - CC�� ������ ���� ��� ��ų ����� �����ϰ� ���� ���
*   - �۷ι� ��ٿ����� ��ų�� ������ ���
*   - ������� ���� ��� ��ų�� ����� �� �α׸� ����� ���� ��� ��
*/
// ������ ����
GameplayAbility::GameplayAbility() {
    // Activate ��� ������ '�ƹ��͵� ���� �ʴ�' �⺻ ���� �Լ��� �ʱ�ȭ�մϴ�.
    // �̷��� �ϸ� �������� �������ϴ�.
    Activate = [](AbilitySystemComponent* SourceASC, AbilitySystemComponent* TargetASC) {
        // �⺻������ �ƹ��͵� ���� ����
        };
}

// CanActivate �Լ��� ���� ����
bool GameplayAbility::CanActivate(AbilitySystemComponent* SourceASC) {
    // ������ �⺻ ���۸� ������, ���߿� ���� ������ ���⿡ �߰��� �� ����
    return true;
}
