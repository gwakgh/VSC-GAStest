#include "MainMenu.h"
#include "ConsoleUtils.h" // gotoxy, setColor �� ��ƿ��Ƽ �Լ�
#include "Player.h"
#include "Monster.h"
#include "MagicClawAbility.h"
#include "BattleManager.h"

#include <conio.h>
#include <iostream>

using namespace std;
using namespace ConsoleUtils; // ��ƿ��Ƽ �Լ� ����� ���� ���ӽ����̽�

// (KEY_UP, KEY_DOWN �� Ű�ڵ� define�� ConsoleUtils.h ���� ������ �ű�� �� �����ϴ�)
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

void gameStart();

MainMenu::MainMenu()
    : m_currentSelection(0), m_isRunning(true) // ��� �ʱ�ȭ ����Ʈ ���
{
    m_menuItems = { "�̱��÷���", "��Ƽ�÷���", "����", "ũ����", "���� ����" };
}

void MainMenu::run() {
    while (m_isRunning) {
        draw();
        handleInput();
    }
}

void MainMenu::handleInput() {
    int key = _getch();
    if (key == 224) { // ����Ű
        key = _getch();
        switch (key) {
        case KEY_UP:
            m_currentSelection--;
            if (m_currentSelection < 0) m_currentSelection = m_menuItems.size() - 1;
            break;
        case KEY_DOWN:
            m_currentSelection++;
            if (m_currentSelection >= m_menuItems.size()) m_currentSelection = 0;
            break;
        }
    }
    else if (key == KEY_ENTER) {
        switch (m_currentSelection) {
        case 0: gameStart(); break;
        case 1:  break;
        case 2: /* settings(); */ break;
        case 3: /* credits(); */ break;
        case 4:
            m_isRunning = false; // ���� ����
            break;
        }
    }
}

void MainMenu::draw() {
    system("cls");
    // ������ drawMenu �Լ� ������ �״�� �����ɴϴ�.
    // ��, �Ű����� ��� ��� ���� m_menuItems�� m_currentSelection�� ����մϴ�.
    // ... (ASCII ��Ʈ �� �޴� �׸� �׸��� �ڵ�) ...
    for (int i = 0; i < m_menuItems.size(); ++i) {
        gotoxy(32, 14 + i * 2);
        if (i == m_currentSelection) {
            // ... ���̶���Ʈ ǥ��
        }
        else {
            // ... �Ϲ� ǥ��
        }
    }
}
void gameStart() {
    system("cls"); // ���� �޴� ȭ���� �����ϰ� ����ϴ�.

    // --- 1. ���� ���� (Player, Monster, Ability �� ����) ---
    // �� ������ �ùٸ� ��ġ�� �ٷ� �����Դϴ�.
    auto player = make_unique<Player>(L"���");
    auto monster = make_unique<Monster>(L"���", 80.0f, 8.0f);

    // �÷��̾�� ��ų �ο�
    auto magicClaw = make_shared<MagicClawAbility>();
    player->GetAbilitySystemComponent()->GrantAbility(magicClaw);
    // (���� �ٸ� ��ų�� �ִٸ� ���⼭ �߰��� �ο��ϸ� �˴ϴ�)

    // --- 2. ���� ���� ---
    wcout << L"������ �����մϴ�..." << endl;
    ConsoleUtils::PlayBattleIntroAnimation();
    Sleep(1000);

    BattleManager battle(*player, *monster);
    battle.Run();

    // --- 3. ���� ���� �� ó�� ---
    // ������ ������ �ٷ� ���� �޴��� ���ư� ȭ���� �������Ƿ�,
    // ������ ����� Ȯ���� �� �ֵ��� ��� ������ִ� ���� �����ϴ�.
    wcout << L"\n\n������ ����Ǿ����ϴ�. ���� �޴��� ���ư����� �ƹ� Ű�� ��������..." << endl;
    _getch(); // �ƹ� Ű�� �Է¹��� ������ ���
}