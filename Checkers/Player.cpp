#include "Player.h"
#include <iostream>

Player::Player() {

}

Player::~Player() {

}

void Player::SetupPlayer(std::string name, CellType cellType) {
	this->name = name;
	this->cellType = cellType;
}

void Player::SetBoard(Board* board)
{
	this->board = board;
}

bool Player::MakeMove()
{
	unsigned int row, col;
	std::cout << "Игрок " << this->name << ", ваш ход..." << std::endl;
	std::cout << "Введите строку: ";
	std::cin >> row;
	std::cout << "Введите столбец: ";
	std::cin >> col;

	if (this->board->CheckLegal(col, row))
	{
		this->board->SetSell(col, row, this->cellType);
		return true;
	}

	return false;
}

std::string Player::GetName()
{
	return this->name;
}
