#pragma once
#include <string>
#include <vector>
#include <memory>

// ���� ����: ��ü ���Ǹ� �������� �ʾƵ� ������/������ ����� �� �ְ� ��
class Player;
class Monster;
class GameplayAbility;

// ������ ���� ���¸� ��Ÿ���� ������
enum class BattleState {
    MainMenu,
    AttackMenu,
    ItemMenu,
    Busy,           // �÷��̾ ���Ͱ� �ൿ �� (�Է� ����)
    BattleEnd
};

class BattleManager {
public:
    // ������: �ο� �÷��̾�� ������ ������ �޽��ϴ�.
    BattleManager(Player& player, Monster& monster);

    // ���� ������ �����ϰ� �����ϴ� ���� �Լ�
    void Run();

private:
    // ��� ������ ������ ��� ���¸� �����մϴ�.
    Player& m_player;
    Monster& m_monster;

    BattleState m_currentState;
    int m_mainMenuSelection;
    int m_attackMenuSelection;
    int m_itemMenuSelection;
    std::wstring m_statusMessage;

    // ���ο����� ����� private ����� �Լ���
    void ProcessInput(); // �Է��� �޾� ���¸� �����ϴ� �Լ�
    void UpdateGame();   // �ൿ �� ���� ���¸� �����ϴ� �Լ�
    void Draw();         // ���� ���¸� ȭ�鿡 �׸��� �Լ�
};