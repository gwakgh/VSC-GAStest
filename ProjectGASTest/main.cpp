#include <iostream>
#include <memory>
#include <clocale>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <windows.h>

#include "Player.h"
#include "Monster.h"
#include "MagicClawAbility.h"
#include "BattleManager.h"
#include "ConsoleUtils.h"
#include "MainMenu.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");
    _setmode(_fileno(stdout), _O_U16TEXT);

    // --- 1. 게임 설정 ---
    auto player = make_unique<Player>(L"용사");
    auto monster = make_unique<Monster>(L"고블린", 80.0f, 8.0f);

    auto magicClaw = make_shared<MagicClawAbility>();
    player->GetAbilitySystemComponent()->GrantAbility(magicClaw);

    // --- 2. 전투 시작 ---
    wcout << L"전투를 시작합니다..." << endl;
    ConsoleUtils::PlayBattleIntroAnimation();
    Sleep(1000);
    BattleManager battle(*player, *monster);
    battle.Run();

    // --- 3. 전투 종료 ---
    wcout << L"\n\n전투가 종료되었습니다." << endl;
    wcout << L"Press any key to exit..." << endl;
    _getch();

    return 0;
}
