#include <iostream>
#include "Player.h"
#include "MoveTypes.h"

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
	std::string position;


	Checker* selectedChecker = nullptr;
	bool hasSelectedChecker = this->board->CheckIfPlayerHasSelectedCheckers();

	if (hasSelectedChecker) {
		selectedChecker = this->board->GetSelectedChecker();
	}
	else {
		std::cout << "Игрок " << this->name << ", ваш ход..." << std::endl;
		std::cout << "Выберите шашку: (координаты в виде A1)";
		std::cin >> position;
	}

	if (!hasSelectedChecker && this->board->CheckIfPositionIsCorrect(position)) {
		std::pair<int, int> coords = this->board->ParsePosition(position);
		selectedChecker = this->board->GetChecker(coords.first, coords.second);
	}

	if (selectedChecker == nullptr) {
		std::cout << "Шашка была выбрана неправильно!" << std::endl;
		return false;
	}

	if (selectedChecker->player != this->cellType) {
		std::cout << "Вы выбрали шашку другого игрока!" << std::endl;
		return false;
	}

	if ((!this->board->continuousJump || hasSelectedChecker) && selectedChecker->allowedToMove) {
		this->board->DeselectAllCheckers();
		selectedChecker->selected = true;
	}
	else {
		std::string exists = "Существует атака для другой шашки, пожалуйста выберите другую";
		std::string continious = "Существует продолжительная атака, пожалуйста, прыгайте той же шашкой";
		std::string message = !this->board->continuousJump ? exists : continious;
		std::cout << message << std::endl;
		return false;
	}

	std::cout << "Выберите место, куда должна пойти шашка (координаты в виде A1): ";
	std::cin >> position;


	EmptyCell* selectedCell = nullptr;
	if (this->board->CheckIfPositionIsCorrect(position)) {
		std::pair<int, int> coords = this->board->ParsePosition(position);
		selectedCell = this->board->GetEmptyCell(coords.first, coords.second);

		if (!this->board->continuousJump) {
			this->board->DeselectAllCheckers();
		}
	}

	if (selectedCell == nullptr) {
		std::cout << "Клетка была выбрана неправильно!" << std::endl;

		if (!this->board->continuousJump) {
			this->board->DeselectAllCheckers();
		}

		return false;
	}

	MoveTypes inRange = selectedCell->InRange(selectedChecker);
	if (inRange != MoveTypes::Wrong) {
		if (inRange == MoveTypes::Jump) {
			if (selectedChecker->OpponentJump(selectedCell->position.first, selectedCell->position.second)) {
				selectedChecker->Move(selectedCell->position.first, selectedCell->position.second);
				if (selectedChecker->CanJumpAny()) {
					selectedChecker->selected = true;
					this->board->continuousJump = true;
				}
				else {
					this->board->ChangePlayerTurn();
				}
				return true;
			}
		}
		else if (inRange == MoveTypes::RegularMove && !this->board->jumpExist) {
			if (!selectedChecker->CanJumpAny()) {
				selectedChecker->Move(selectedCell->position.first, selectedCell->position.second);
				this->board->ChangePlayerTurn();
				return true;
			}
			else {
				std::cout << "Вы должны атаковать!" << std::endl;
			}
		}
	}

	return false;
}

std::string Player::GetName()
{
	return this->name;
}
