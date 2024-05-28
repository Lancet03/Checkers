#pragma once
#include "Board.h"
#include "CellType.h"
#include "BoardTile.h"
#include "Printer.h"
#include "EmptyCell.h"
#include "Checker.h"

#include <vector>
#include <string>
#include <utility>

class Tile;

//struct Score {
//	int player1 = 0;
//	int player2 = 0;
//};

class BoardMonteCarloEvaluator
{
private:
	Board* board;
	bool isVictory;
	//Score score;
	int numGames;
	int numVictories;
	int numLosses;
	int numDraws;

	std::pair<int, int> checkerPos, tilePos;
	BoardTile startCheckerType;
public:
	bool jumpExist = false;
	bool continuousJump = false;
	int playerTurn = 1;

	BoardMonteCarloEvaluator(Board* board, int numIterations, BoardTile startCheckerType, std::pair<int, int> checkerPos, std::pair<int, int> tilePos);
	virtual ~BoardMonteCarloEvaluator();

	std::vector <std::vector<Tile*>> cells;
	std::vector <EmptyCell*> emptyCells;
	std::vector <Checker*> checkers;

	/*void Show();
	bool CheckLegal(int xpos, int ypos);
	bool CheckEndCondition();
	bool IsVictory();

	void PrintCell(int row, int col);

	bool IsValidPlaceToMove(int row, int col);
	void ChangePlayerTurn();
	int CheckIfSomeoneWon();
	void Clear();

	void CheckIfJumpExists();
	bool CheckIfPositionOnBoard(int x, int y);
	bool CheckIfPositionIsCorrect(std::string position);
	bool CheckIfCheckerOnPosition(int x, int y);
	bool CheckIfEmptyCellOnPosition(int x, int y);

	Checker* GetChecker(int x, int y);
	EmptyCell* GetEmptyCell(int x, int y);
	void RemoveChecker(Checker* checker);

	std::pair<int, int> ParsePosition(std::string position);

	Checker* GetSelectedChecker();
	bool CheckIfPlayerHasSelectedCheckers();
	void DeselectAllCheckers();

	std::vector<Checker*> GetCheckersThatCanMove();*/
	void EvaluateBoard();
	void Evaluate();
	int GetVictories() { return numVictories; };
	int GetLosses() { return numLosses; };
	int GetDraws() { return numDraws; };
	std::pair<int, int> GetCheckerPos() { return checkerPos; };
	std::pair<int, int> GetTilePos() { return tilePos; };
};

