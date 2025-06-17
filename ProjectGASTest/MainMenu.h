#pragma once
#include <vector>
#include <string>

class MainMenu {
public:
    // ������: �޴� �׸���� �޾� �ʱ�ȭ�մϴ�.
    MainMenu();

    // �޴��� �����ϴ� ���� ���� �Լ��Դϴ�.
    void run();

private:
    // �޴��� ȭ�鿡 �׸��ϴ�.
    void draw();

    // ����� �Է��� ó���մϴ�.
    void handleInput();

    // �޴� �׸��
    std::vector<std::string> m_menuItems;

    // ���� ���õ� �׸��� �ε���
    int m_currentSelection;

    // �޴� ������ ������� ����
    bool m_isRunning;
};