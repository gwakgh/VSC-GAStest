#include "ConsoleUtils.h"
#include <iostream>
#include <random> // C++ 표준 난수 라이브러리 헤더

using namespace std;

namespace ConsoleUtils {

    void gotoxy(int x, int y) {
        COORD pos = { (SHORT)(x * 2), (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void clearScreen() {
        system("cls");
    }

    wstring drawHealthBar(float currentHp, float maxHp, int barLength) {
        if (currentHp < 0) currentHp = 0;
        float ratio = currentHp / maxHp;
        int filledLength = static_cast<int>(ratio * barLength);
        wstring bar = L"HP [";
        for (int i = 0; i < barLength; ++i) {
            if (i < filledLength) bar += L"■";
            else bar += L" ";
        }
        bar += L"]";
        return bar;
    }

    void drawBox(int x, int y, int width, int height) {
        gotoxy(x, y); wcout << L"┌";
        for (int i = 0; i < width - 2; ++i) wcout << L"─";
        wcout << L"┐";
        for (int i = 1; i < height - 1; ++i) {
            gotoxy(x, y + i); wcout << L"│";
            gotoxy(x + width - 1, y + i); wcout << L"│";
        }
        gotoxy(x, y + height - 1); wcout << L"└";
        for (int i = 0; i < width - 2; ++i) wcout << L"─";
        wcout << L"┘";
    }

    void PlayBattleIntroAnimation() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        for (int i = 0; i < 2; ++i) {
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
            clearScreen();
            Sleep(60);
            SetConsoleTextAttribute(hConsole, 0);
            clearScreen();
            Sleep(60);
        }

        wstring line(screenWidth, L'█');
        for (int i = 0; i < screenHeight; i += 2) {
            gotoxy(0, i);
            wcout << line;
            gotoxy(0, screenHeight - 1 - i);
            wcout << line;
            Sleep(30);
        }

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        clearScreen();
    }

    // min과 max 사이의 정수 난수를 반환하는 함수
    int GetRandomInt(int min, int max) {
        // static 키워드: 이 변수들이 프로그램 시작 시 딱 한 번만 초기화되도록 보장합니다.

        // 1. 하드웨어 기반의 예측 불가능한 시드 생성기
        static std::random_device rd;

        // 2. 고품질 난수 생성 엔진 (Mersenne Twister 알고리즘)
        // 위에서 만든 시드 생성기로 엔진을 초기화합니다.
        static std::mt19937 gen(rd());

        // 3. 균등 분포 설정: min과 max 사이의 모든 정수가 동일한 확률로 나오도록 합니다.
        std::uniform_int_distribution<> dis(min, max);

        // 엔진을 사용해 분포에 맞는 난수를 생성하고 반환합니다.
        return dis(gen);
    }

    // min과 max 사이의 실수 난수를 반환하는 함수
    float GetRandomFloat(float min, float max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        // 실수(float)를 위한 균등 분포 설정
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
} 