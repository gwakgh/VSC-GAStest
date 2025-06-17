#pragma once
#include <string>
#include <windows.h> // COORD, HANDLE 등 Windows API 사용을 위해 필요

namespace ConsoleUtils {
    // 함수 전방 선언 (프로토타입)
    void gotoxy(int x, int y);
    void clearScreen();
    std::wstring drawHealthBar(float currentHp, float maxHp, int barLength = 10);
    void drawBox(int x, int y, int width, int height);
    void PlayBattleIntroAnimation(); // 전투 인트로 애니메이션도 범용 기능이므로 이곳으로 이동

    //min과 max 사이의 정수 난수를 반환하는 함수 선언
    int GetRandomInt(int min, int max);
    float GetRandomFloat(float min, float max);
}