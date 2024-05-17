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
