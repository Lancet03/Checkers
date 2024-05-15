#include "Player.h"
#include <iostream>

Player::Player() {

}

Player::~Player() {

}

void Player::SetupPlayer(std::string name, BoardTile cellType) {
	this->name = name;
	this->cellType = cellType;
}

void Player::SetBoard(Board* board)
{
	this->board = board;
}

bool Player::MakeMove()
{
	unsigned int row = 0, col = 0;
	std::string position;
	//char* position;
	std::cout << "Игрок " << this->name << ", ваш ход..." << std::endl;
	std::cout << "Выберите шашку: (координаты в виде A1)";
	std::cin >> position;

	if (this->board->CheckIfPositionIsCorrect(position)) {
		this->board->SetSell(col, row, this->cellType);
		return true;
	}


	
	//if (this->board->CheckIfCheckerSelected(col, row))
	//{

	//	this->board->SetSell(col, row, this->cellType);
	//	return true;
	//}

	return false;
}

std::string Player::GetName()
{
	return this->name;
}
