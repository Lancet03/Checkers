#include "BoardMonteCarloEvaluator.h"

BoardMonteCarloEvaluator::BoardMonteCarloEvaluator(Board* board, int numIterations, BoardTile startCheckerType, std::pair<int, int> checkerPos, std::pair<int, int> tilePos) {
	this->board = board;
	this->numGames = numIterations;
	this->numVictories = 0;
	this->numLosses = 0;
	this->checkerPos = checkerPos;
	this->tilePos = tilePos;
	this->startCheckerType = startCheckerType;
}

BoardMonteCarloEvaluator::~BoardMonteCarloEvaluator() {

}

