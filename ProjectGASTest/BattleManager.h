#pragma once
#include <string>
#include <vector>
#include <memory>

// 전방 선언: 전체 정의를 포함하지 않아도 포인터/참조를 사용할 수 있게 함
class Player;
class Monster;
class GameplayAbility;

// 전투의 현재 상태를 나타내는 열거형
enum class BattleState {
    MainMenu,
    AttackMenu,
    ItemMenu,
    Busy,           // 플레이어나 몬스터가 행동 중 (입력 방지)
    BattleEnd
};

class BattleManager {
public:
    // 생성자: 싸울 플레이어와 몬스터의 참조를 받습니다.
    BattleManager(Player& player, Monster& monster);

    // 전투 루프를 시작하고 실행하는 메인 함수
    void Run();

private:
    // 멤버 변수로 전투의 모든 상태를 관리합니다.
    Player& m_player;
    Monster& m_monster;

    BattleState m_currentState;
    int m_mainMenuSelection;
    int m_attackMenuSelection;
    int m_itemMenuSelection;
    std::wstring m_statusMessage;

    // 내부에서만 사용할 private 도우미 함수들
    void ProcessInput(); // 입력을 받아 상태를 변경하는 함수
    void UpdateGame();   // 행동 후 게임 상태를 점검하는 함수
    void Draw();         // 현재 상태를 화면에 그리는 함수
};