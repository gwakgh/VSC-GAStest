#include "BattleManager.h"
#include "Player.h"
#include "Monster.h"
#include "ConsoleUtils.h"

#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;
using namespace ConsoleUtils;
// --- 생성자 구현 ---
BattleManager::BattleManager(Player& player, Monster& monster)
    : m_player(player),
    m_monster(monster),
    m_currentState(BattleState::MainMenu),
    m_mainMenuSelection(0),
    m_attackMenuSelection(0),
    m_statusMessage(L"야생의 " + monster.GetName() + L"이(가) 나타났다!")
{
}

// --- 전투 루프 실행 함수 구현 ---
void BattleManager::Run() {
    // [개선됨] BattleEnd 상태가 될 때까지 루프를 실행합니다.
    while (m_currentState != BattleState::BattleEnd) {
        Draw();
        ProcessInput();
        UpdateGame();
    }
    // 루프가 끝나면 전투 종료 메시지를 포함하여 마지막 상태를 한 번 더 그립니다.
    Draw();
}

// --- 입력 처리 함수 구현 ---
void BattleManager::ProcessInput() {
    // 입력을 받아야 하는 상태가 아니면 함수를 바로 종료합니다.
    if (m_currentState != BattleState::MainMenu && m_currentState != BattleState::AttackMenu) {
        return;
    }

    char input = _getch();

    switch (m_currentState) {
    case BattleState::MainMenu:
        if (input == (char)224) {
            input = _getch();
            if (input == 72) m_mainMenuSelection = (m_mainMenuSelection - 1 + 4) % 4;
            else if (input == 80) m_mainMenuSelection = (m_mainMenuSelection + 1) % 4;
        }
        else if (input == 13) {
            switch (m_mainMenuSelection) {
            case 0: // 공격
                m_currentState = BattleState::AttackMenu;
                m_attackMenuSelection = 0;
                m_statusMessage = L"사용할 스킬을 선택하세요.";
                break;
            case 1: // 방어
            {
                m_statusMessage = m_player.GetName() + L"이(가) 방어 태세를 갖췄습니다!";
                GameplayEffect DefendEffect;
                DefendEffect.AttributeToModify = "DefensePower";
                DefendEffect.ModifierValue = 5.0f;
                m_player.GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(DefendEffect);
                m_currentState = BattleState::Busy;
                break;
            }
            case 2: {
                if (m_player.GetInventory().empty()) {
                    m_statusMessage = L"아이템 가방이 비어있습니다!";
                }
                else {
                    m_currentState = BattleState::ItemMenu;
                    m_itemMenuSelection = 0; // 아이템 메뉴 커서를 0으로 초기화
                    m_statusMessage = L"어떤 아이템을 사용할까?";
                }
                break;
            }
            case 3: // 도망가기
                m_statusMessage = L"성공적으로 도망쳤다!";
                m_currentState = BattleState::BattleEnd;
                break;
            }
        }
        break;

    case BattleState::AttackMenu:
        if (input == (char)224) { // 방향키 입력
            input = _getch();
            // [수정] 메뉴 항목은 스킬 슬롯 4개 + 뒤로가기 1개 = 총 5개로 고정
            const int totalAttackMenuItems = 5;
            if (input == 72) { // 위
                m_attackMenuSelection = (m_attackMenuSelection - 1 + totalAttackMenuItems) % totalAttackMenuItems;
            }
            else if (input == 80) { // 아래
                m_attackMenuSelection = (m_attackMenuSelection + 1) % totalAttackMenuItems;
            }
        }
        else if (input == 13) { // 엔터키 입력
            const auto& abilities = m_player.GetAbilitySystemComponent()->GetGrantedAbilities();
            int skillCount = abilities.size();

            // [수정] 선택한 위치에 따라 로직을 명확하게 세분화
            if (m_attackMenuSelection < skillCount) { // 스킬 선택
                // [수정] TryActivateAbility 호출 시 m_statusMessage를 세 번째 인자로 전달
                bool bSuccess = m_player.GetAbilitySystemComponent()->TryActivateAbility(
                    abilities[m_attackMenuSelection]->AbilityName,
                    m_monster.GetAbilitySystemComponent(),
                    m_statusMessage // 결과 메시지를 이 변수에 직접 담아달라고 요청
                );

                if (bSuccess) {
                    m_currentState = BattleState::Busy;
                }
                else {
                    m_statusMessage = L"스킬 발동에 실패했습니다!";
                }
            }
            else if (m_attackMenuSelection == 4) {
                // 2. '뒤로가기'(인덱스 4)를 선택한 경우
                m_currentState = BattleState::MainMenu;
                m_mainMenuSelection = 0;
                m_statusMessage = L"무엇을 할까?";
            }
            else {
                // 3. 비어있는 '-' 슬롯을 선택한 경우
                m_statusMessage = L"선택할 수 없는 슬롯입니다!";
            }
        }
        break; // AttackMenu case 끝

    default:
        break;
    }
}

// --- 게임 상태 업데이트 함수 구현 ---
void BattleManager::UpdateGame() {
    // 행동이 끝난 후(Busy 상태일 때) 다음 턴으로 넘기는 로직
    if (m_currentState == BattleState::Busy) {
        Draw(); // 행동 결과를 먼저 화면에 그림
        Sleep(1500);

        // 몬스터의 HP 확인
        if (m_monster.GetAbilitySystemComponent()->GetAttributes()->Health <= 0) {
            m_statusMessage = m_monster.GetName() + L"을(를) 물리쳤다!";
            m_currentState = BattleState::BattleEnd;
            return; // 전투 종료
        }

        // TODO: 여기서 몬스터의 턴 (AI 로직) 진행
        m_statusMessage = m_monster.GetName() + L"의 차례... (미구현)";
        Draw();
        Sleep(1500);

        // 플레이어 턴으로 복귀
        m_currentState = BattleState::MainMenu;
        m_statusMessage = L"무엇을 할까?";
    }
}

void BattleManager::Draw() {
    clearScreen();

    auto playerAttrs = m_player.GetAbilitySystemComponent()->GetAttributes();
    auto monsterAttrs = m_monster.GetAbilitySystemComponent()->GetAttributes();

    // --- 적 정보 UI ---
    drawBox(24, 2, 16, 6); // [수정] 박스 높이 5 -> 6
    gotoxy(25, 3); wcout << m_monster.GetName().c_str();
    gotoxy(35, 3); wcout << L"Lv.5";
    gotoxy(25, 4); wcout << drawHealthBar((size_t)monsterAttrs->Health, monsterAttrs->MaxHealth);
    // [추가] 몬스터 체력 숫자 표시
    gotoxy(25, 5); wcout << (size_t)monsterAttrs->Health << L"/" << monsterAttrs->MaxHealth;

    // --- 플레이어 정보 UI ---
    drawBox(2, 10, 18, 7); // [수정] 박스 높이 6 -> 7
    gotoxy(3, 11); wcout << m_player.GetName().c_str();
    gotoxy(15, 11); wcout << L"Lv.7";
    gotoxy(3, 12); wcout << drawHealthBar(playerAttrs->Health, playerAttrs->MaxHealth);
    gotoxy(3, 13); wcout << (size_t)playerAttrs->Health << L"/" << playerAttrs->MaxHealth;
    // [추가] 플레이어 마나 숫자 표시
    gotoxy(3, 14); wcout << L"MP: " << (size_t)playerAttrs->Mana << L"/" << playerAttrs->MaxMana;


    // --- 하단 UI (메시지, 메뉴) ---
    drawBox(0, 18, 40, 8);
    drawBox(22, 18, 18, 8);
    gotoxy(2, 19); wcout << m_statusMessage;

    // --- 상태별 메뉴 그리기 ---
    if (m_currentState == BattleState::MainMenu) {
        vector<wstring> options = { L"공격", L"방어", L"아이템", L"도망가기" };
        for (int i = 0; i < options.size(); ++i) {
            gotoxy(24, 20 + i);
            if (i == m_mainMenuSelection) wcout << L"> " << options[i];
            else wcout << L"  " << options[i];
        }
    }
    else if (m_currentState == BattleState::AttackMenu) {
        // [개선된 최종 로직]
        // 1. 화면에 표시할 모든 메뉴 항목을 하나의 vector에 담습니다.
        vector<wstring> attackOptions;
        const auto& abilities = m_player.GetAbilitySystemComponent()->GetGrantedAbilities();
        for (const auto& ability : abilities) {
            attackOptions.push_back(ability->AbilityName);
        }
        while (attackOptions.size() < 4) { // 4칸을 채울 때까지 빈 슬롯 추가
            attackOptions.push_back(L"-");
        }
        attackOptions.push_back(L"뒤로가기"); // 마지막에 '뒤로가기' 추가

        // 2. 이제 이 vector를 기반으로 하나의 루프만 사용하여 메뉴를 그립니다.
        for (int i = 0; i < attackOptions.size(); ++i) {
            gotoxy(24, 20 + i);
            if (i == m_attackMenuSelection) {
                wcout << L"> " << attackOptions[i].c_str();
            }
            else {
                wcout << L"  " << attackOptions[i].c_str();
            }
        }
    }
    // Busy나 BattleEnd 상태일 때는 오른쪽 메뉴를 그리지 않습니다.

    gotoxy(0, 26);
}