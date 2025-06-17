#pragma once
#include <vector>
#include <string>

class MainMenu {
public:
    // 생성자: 메뉴 항목들을 받아 초기화합니다.
    MainMenu();

    // 메뉴를 실행하는 메인 루프 함수입니다.
    void run();

private:
    // 메뉴를 화면에 그립니다.
    void draw();

    // 사용자 입력을 처리합니다.
    void handleInput();

    // 메뉴 항목들
    std::vector<std::string> m_menuItems;

    // 현재 선택된 항목의 인덱스
    int m_currentSelection;

    // 메뉴 루프를 계속할지 여부
    bool m_isRunning;
};