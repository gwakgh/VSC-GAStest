#pragma once
#include <string>
#include <windows.h> // COORD, HANDLE �� Windows API ����� ���� �ʿ�

namespace ConsoleUtils {
    // �Լ� ���� ���� (������Ÿ��)
    void gotoxy(int x, int y);
    void clearScreen();
    std::wstring drawHealthBar(float currentHp, float maxHp, int barLength = 10);
    void drawBox(int x, int y, int width, int height);
    void PlayBattleIntroAnimation(); // ���� ��Ʈ�� �ִϸ��̼ǵ� ���� ����̹Ƿ� �̰����� �̵�

    //min�� max ������ ���� ������ ��ȯ�ϴ� �Լ� ����
    int GetRandomInt(int min, int max);
    float GetRandomFloat(float min, float max);
}