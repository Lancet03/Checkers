#include "Manager.h"
#include <iostream>

Manager::Manager() {

}

Manager::~Manager() {
	delete this->p2;
	delete this->p1;
	delete this->board;
}

bool Manager::Init() {
	/*unsigned int boardSize;
	std::string playerName;
	std::cout << "Введите число клеток поля (3-6): ";
	std::cin >> boardSize;
	if ((boardSize < 3) || (boardSize > 6))
	{
		std::cout << "Неверное число клеток поля" << std::endl;
		return false;
	}*/
	unsigned int boardSize = 3;
	this->board = new Board(boardSize);
	std::string playerName = "a";
	this->p1 = new Player();
	this->p2 = new Player();
	//std::cin.ignore();
	std::cout << "Введите имя игрока, играющего Х: ";
	//getline(std::cin, playerName);
	this->p1->SetupPlayer(playerName, CellType_WhiteChecker);
	std::cout << "Введите имя игрока, играющего за O: ";
	//getline(std::cin, playerName);
	this->p2->SetupPlayer(playerName, CellType_BlackChecker);
	this->p1->SetBoard(this->board);
	this->p2->SetBoard(this->board);
	this->currentPlayer = this->p1;

	return true;
}

void Manager::ShowBoard() {
	this->board->Show();
}

void Manager::MakeMove() {
	this->ShowBoard();
	while (!currentPlayer->MakeMove()) {
		std::cout << "Недопустимый ход, попробуйте ещё раз" << std::endl;
		this->ShowBoard();
	}

	if (this->board->CheckEndCondition()) {
		if (this->board->IsVictory()) {
			std::cout << "Player " << this->currentPlayer->GetName() << " won!" << std::endl;
		}
		else {
			std::cout << "Ничья!" << std::endl;
		}

		this->isGameFinished = true;
		this->ShowBoard();

		return;
	}

	this->currentPlayer = (currentPlayer == this->p1) ? this->p2 : this->p1;
}

bool Manager::IsGameFinished() {
	return this->isGameFinished;
}