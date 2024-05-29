#include "ComputerPlayer.h"
#include "BoardMonteCarloEvaluator.h"
#include "Checker.h"
#include "EmptyCell.h"
#include "BoardTile.h"

#include <iostream>
#include <vector>
#include <utility>

ComputerPlayer::ComputerPlayer() {

}

ComputerPlayer::~ComputerPlayer() {

}

bool ComputerPlayer::MakeMove() {
	std::vector<BoardMonteCarloEvaluator*> evaluators;
	
	std::vector<Checker*> checkersThatCanMove = this->board->GetCheckersThatCanMove();
	for (int i = 0; i < checkersThatCanMove.size(); i++) {
		Checker* checkerThatCanMove = checkersThatCanMove[i];
		std::vector<EmptyCell*> availableToMoveCells = checkerThatCanMove->GetTilesAvailable();

		for (int j = 0; j < availableToMoveCells.size(); j++) {
			EmptyCell* availableToMoveCell = availableToMoveCells[j];
			BoardMonteCarloEvaluator* evaluator = new BoardMonteCarloEvaluator(this->board, 1000, this->cellType, checkerThatCanMove->position, availableToMoveCell->position);
			evaluators.push_back(evaluator);
		}
	}


	for (int i = 0; i < evaluators.size(); i++) {
		evaluators[i]->Evaluate();
	}

	int biggestVictories = -1;
	int biggestDraws = -1;

	for (int i = 0; i < evaluators.size(); i++) {
		if (this->cellType == BoardTile::White) {
			if (evaluators[i]->GetVictories() > biggestVictories) {
				biggestVictories = evaluators[i]->GetVictories();
			}

		}
		else {
			if (evaluators[i]->GetLosses() > biggestVictories) {
				biggestVictories = evaluators[i]->GetLosses();
			}
		}

		if (evaluators[i]->GetDraws() > biggestDraws) {
			biggestDraws = evaluators[i]->GetDraws();
		}
	}

	std::vector<BoardMonteCarloEvaluator*> biggestWinEvaluators;
	std::vector<BoardMonteCarloEvaluator*> biggestDrawsEvaluators;
	for (int i = 0; i < evaluators.size(); i++) {
		int numVictories, numDraws;
		if (this->cellType == BoardTile::White) {
			numVictories = evaluators[i]->GetVictories();
		}
		else {
			numVictories = evaluators[i]->GetLosses();
		}
		numDraws = evaluators[i]->GetDraws();

		if (numVictories == biggestVictories) {
			biggestWinEvaluators.push_back(evaluators[i]);
		}
		if (numDraws == biggestDraws) {
			biggestDrawsEvaluators.push_back(evaluators[i]);
		}
	}

	std::pair<int, int> checkerToMovePos;
	std::pair<int, int> moveToTilePos;
	if (biggestWinEvaluators.size() > 0) {
		checkerToMovePos = biggestWinEvaluators[0]->GetFirstMoveCheckerPos();
		moveToTilePos = biggestWinEvaluators[0]->GetFirstMoveTilePos();
	}
	else {
		checkerToMovePos = biggestDrawsEvaluators[0]->GetFirstMoveCheckerPos();
		moveToTilePos = biggestDrawsEvaluators[0]->GetFirstMoveTilePos();
	}

	Checker* checkerToMove = this->board->GetChecker(checkerToMovePos.first, checkerToMovePos.second);
	if (checkerToMove == nullptr) {
		std::cout << "Computer Player Error:: Should get Checker";
		/*return false;*/
	}
	bool isMoveSuccess = checkerToMove->Move(moveToTilePos.first, moveToTilePos.second);

	if (!isMoveSuccess) {
		std::cout << "Computer Player Error:: should move successfully";
	}


	for (int i = 0; i < evaluators.size(); i++) {
		delete evaluators[i];
	}
	evaluators.clear();
	biggestWinEvaluators.clear();
	biggestDrawsEvaluators.clear();

	

	return isMoveSuccess;
}

//CheckerMove ComputerPlayer::CalcMove() {
//	std::vector<BoardMonteCarloEvaluator*> evaluators;
//
//	std::vector<Checker*> checkersThatCanMove = this->board->GetCheckersThatCanMove();
//	for (int i = 0; i < checkersThatCanMove.size(); i++) {
//		Checker* checkerThatCanMove = checkersThatCanMove[i];
//		std::vector<EmptyCell*> availableToMoveCells = checkerThatCanMove->GetTilesAvailable();
//
//		for (int j = 0; j < availableToMoveCells.size(); j++) {
//			EmptyCell* availableToMoveCell = availableToMoveCells[j];
//			BoardMonteCarloEvaluator* evaluator = new BoardMonteCarloEvaluator(this->board, 1000, this->cellType, checkerThatCanMove->position, availableToMoveCell->position);
//			evaluators.push_back(evaluator);
//		}
//	}
//
//
//	for (int i = 0; i < evaluators.size(); i++) {
//		evaluators[i]->Evaluate();
//	}
//
//	int biggestVictories = -1;
//	int biggestDraws = -1;
//
//	for (int i = 0; i < evaluators.size(); i++) {
//		if (this->cellType == BoardTile::White) {
//			if (evaluators[i]->GetVictories() > biggestVictories) {
//				biggestVictories = evaluators[i]->GetVictories();
//			}
//
//		}
//		else {
//			if (evaluators[i]->GetLosses() > biggestVictories) {
//				biggestVictories = evaluators[i]->GetLosses();
//			}
//		}
//
//		if (evaluators[i]->GetDraws() > biggestDraws) {
//			biggestDraws = evaluators[i]->GetDraws();
//		}
//	}
//
//	std::vector<BoardMonteCarloEvaluator*> biggestWinEvaluators;
//	std::vector<BoardMonteCarloEvaluator*> biggestDrawsEvaluators;
//	for (int i = 0; i < evaluators.size(); i++) {
//		int numVictories, numDraws;
//		if (this->cellType == BoardTile::White) {
//			numVictories = evaluators[i]->GetVictories();
//		}
//		else {
//			numVictories = evaluators[i]->GetLosses();
//		}
//		numDraws = evaluators[i]->GetDraws();
//
//		if (numVictories == biggestVictories) {
//			biggestWinEvaluators.push_back(evaluators[i]);
//		}
//		if (numDraws == biggestDraws) {
//			biggestDrawsEvaluators.push_back(evaluators[i]);
//		}
//	}
//
//	std::pair<int, int> checkerToMovePos;
//	std::pair<int, int> moveToTilePos;
//	if (biggestWinEvaluators.size() > 0) {
//		checkerToMovePos = biggestWinEvaluators[0]->GetFirstMoveCheckerPos();
//		moveToTilePos = biggestWinEvaluators[0]->GetFirstMoveTilePos();
//	}
//	else {
//		checkerToMovePos = biggestDrawsEvaluators[0]->GetFirstMoveCheckerPos();
//		moveToTilePos = biggestDrawsEvaluators[0]->GetFirstMoveTilePos();
//	}
//
//	CheckerMove checkerMove;
//	checkerMove.checkerPos = checkerToMovePos;
//	checkerMove.moveToPos = moveToTilePos;
//
//	for (int i = 0; i < evaluators.size(); i++) {
//		delete evaluators[i];
//	}
//	evaluators.clear();
//	biggestWinEvaluators.clear();
//	biggestDrawsEvaluators.clear();
//
//	return checkerMove;
//}