#include <iostream>
#include <conio.h>
#include <ctype.h>

#include "Board.h"
#include "Manager.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    Manager manager;
    if (!manager.Init())
    {
        std::cout << "Неверные данные, выходим...";
        _getch();
        return 0;
    }
    while (!manager.IsGameFinished())
    {
        manager.MakeMove();
    }
    _getch();

    return 0;
}

std::string Checker::GetTextPosition() {
    char xPos = 'A' + this->position.first;
    char yPos = '1' + this->position.second;

    std::string val = std::string(1, xPos) + yPos;

    return val;
}
