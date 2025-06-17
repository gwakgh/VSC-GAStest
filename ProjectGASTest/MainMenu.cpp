#include "MainMenu.h"
#include "ConsoleUtils.h" // gotoxy, setColor 등 유틸리티 함수
#include "Player.h"
#include "Monster.h"
#include "MagicClawAbility.h"
#include "BattleManager.h"

#include <conio.h>
#include <iostream>

using namespace std;
using namespace ConsoleUtils; // 유틸리티 함수 사용을 위한 네임스페이스

// (KEY_UP, KEY_DOWN 등 키코드 define은 ConsoleUtils.h 같은 곳으로 옮기면 더 좋습니다)
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

void gameStart();

MainMenu::MainMenu()
    : m_currentSelection(0), m_isRunning(true) // 멤버 초기화 리스트 사용
{
    m_menuItems = { "싱글플레이", "멀티플레이", "설정", "크레딧", "게임 종료" };
}

void MainMenu::run() {
    while (m_isRunning) {
        draw();
        handleInput();
    }
}

void MainMenu::handleInput() {
    int key = _getch();
    if (key == 224) { // 방향키
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
            m_isRunning = false; // 루프 종료
            break;
        }
    }
}

void MainMenu::draw() {
    system("cls");
    // 기존의 drawMenu 함수 내용을 그대로 가져옵니다.
    // 단, 매개변수 대신 멤버 변수 m_menuItems와 m_currentSelection을 사용합니다.
    // ... (ASCII 아트 및 메뉴 항목 그리는 코드) ...
    for (int i = 0; i < m_menuItems.size(); ++i) {
        gotoxy(32, 14 + i * 2);
        if (i == m_currentSelection) {
            // ... 하이라이트 표시
        }
        else {
            // ... 일반 표시
        }
    }
}
void gameStart() {
    system("cls"); // 이전 메뉴 화면을 깨끗하게 지웁니다.

    // --- 1. 게임 설정 (Player, Monster, Ability 등 생성) ---
    // 이 로직의 올바른 위치는 바로 여기입니다.
    auto player = make_unique<Player>(L"용사");
    auto monster = make_unique<Monster>(L"고블린", 80.0f, 8.0f);

    // 플레이어에게 스킬 부여
    auto magicClaw = make_shared<MagicClawAbility>();
    player->GetAbilitySystemComponent()->GrantAbility(magicClaw);
    // (만약 다른 스킬이 있다면 여기서 추가로 부여하면 됩니다)

    // --- 2. 전투 시작 ---
    wcout << L"전투를 시작합니다..." << endl;
    ConsoleUtils::PlayBattleIntroAnimation();
    Sleep(1000);

    BattleManager battle(*player, *monster);
    battle.Run();

    // --- 3. 전투 종료 후 처리 ---
    // 전투가 끝나면 바로 메인 메뉴로 돌아가 화면이 지워지므로,
    // 유저가 결과를 확인할 수 있도록 잠시 대기해주는 것이 좋습니다.
    wcout << L"\n\n전투가 종료되었습니다. 메인 메뉴로 돌아가려면 아무 키나 누르세요..." << endl;
    _getch(); // 아무 키나 입력받을 때까지 대기
}