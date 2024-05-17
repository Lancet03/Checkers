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
	this->board = new Board();
	std::string playerName;
	this->p1 = new Player();
	this->p2 = new Player();

	std::cout << "Введите имя игрока, играющего белыми шашками: ";
	getline(std::cin, playerName);
	this->p1->SetupPlayer(playerName, BoardTile::White);
	std::cout << "Введите имя игрока, играющего черными шашками: ";
	getline(std::cin, playerName);
	playerName = "PlBlack";
	this->p2->SetupPlayer(playerName, BoardTile::Black);
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
	while (!this->currentPlayer->MakeMove()) {
		std::cout << "Недопустимый ход, попробуйте ещё раз" << std::endl;
		this->ShowBoard();
	}

	if (this->board->CheckEndCondition()) {
		if (this->board->IsVictory()) {
			std::cout << "Player " << this->currentPlayer->GetName() << " won!" << std::endl;
		}

		this->isGameFinished = true;
		this->ShowBoard();

		return;
	}

	if (this->currentPlayer->cellType != this->board->playerTurn) {
		this->currentPlayer = (currentPlayer == this->p1) ? this->p2 : this->p1;
	}
}

bool Manager::IsGameFinished() {
	return this->isGameFinished;
}