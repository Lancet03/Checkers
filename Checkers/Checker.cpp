#include "Checker.h"
#include "EmptyCell.h"
#include "Tile.h"
#include "Board.h"

Checker::Checker(int row, int col, int player, Board* board) {
	this->position.first = col;
	this->position.second = row;

	this->player = player;
	this->board = board;
}

void Checker::MakeKing() {
	this->king = true;
}

bool Checker::Move(int x, int y) {
	if (!this->board->IsValidPlaceToMove(y, x)) return false;
	
	if (this->player == 1 && this->king == false) {
		if (y < this->position.second) return false;
	}
	else if (this->player == 2 && this->king == false) {
		if (y > this->position.second) return false;
	}

	Tile* emptyCell = this->board->cells[y][x];
	emptyCell->SetPostion(this->position.first, this->position.second);
	int xCheckerPos = this->position.first;
	int yCheckerPos = this->position.second;
	this->board->cells[yCheckerPos][xCheckerPos] = emptyCell;
	this->SetPostion(x, y);
	this->board->cells[y][x] = this;
	
	if (!this->king && (this->position.second == 0) || this->position.second == (this->board->cells.size() - 1)) {
		this->MakeKing();
	}
	return true;
}

bool Checker::CanJumpAny() {
	int x = this->position.first;
	int y = this->position.second;

	return (this->CanOpponentJump(x + 2, y + 2) != nullptr ||
			this->CanOpponentJump(x - 2, y + 2) != nullptr ||
			this->CanOpponentJump(x + 2, y - 2) != nullptr ||
			this->CanOpponentJump(x - 2, y - 2) != nullptr);
}

Checker* Checker::CanOpponentJump(int x, int y) {
	int dx = x - this->position.first;
	int dy = y - this->position.second;

	if (this->player == 1 && this->king == false) {
		if (y < position.second) return nullptr;
	}
	else if (this->player == 2 && this->king == false) {
		if (y > this->position.second) return nullptr;
	}

	if (!this->board->CheckIfPositionOnBoard(x, y)) return nullptr;

	int tileToCheckX = this->position.first + dx / 2;
	int tileToCheckY = this->position.second + dy / 2;
	if (!this->board->CheckIfPositionOnBoard(tileToCheckX, tileToCheckY)) return nullptr;
	
	if (!this->board->IsValidPlaceToMove(tileToCheckY, tileToCheckX) && this->board->IsValidPlaceToMove(y, x)) {
		std::vector<Checker*> checkers = this->board->checkers;
		for (int checkerId = 0; checkerId < checkers.size(); checkerId++) {
			Checker* checker = checkers[checkerId];
			if (checker->position.first == tileToCheckX && checker->position.second == tileToCheckY) {
				if (this->player != checker->player) {
					return checker;
				}
			}
		}
	}

	return nullptr;
}

bool Checker::OpponentJump(int x, int y) {
	Checker* checkerToRemove = this->CanOpponentJump(x, y);

	if (checkerToRemove != nullptr) {
		checkerToRemove->Remove();
		return true;
	}
	return false;
}

void Checker::Remove() {
	this->board->RemoveChecker(this);
}
