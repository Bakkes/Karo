#include "StaticEvaluation.h"

namespace engine {
	StaticEvaluation::StaticEvaluation(void)
	{
		_flippedValue = 50;
		_blockedTileValue = 8;
		_cornerValue = 9;
		_neighborValue = 11;
		_lineValue = 25;

		_centerValue = 5;
		_semiCenterValue = 4;
		_centerColumnValue = 3;
		_bottomOrTopRowValue = 2;
		_cornerValue2 = 1;
	}

	StaticEvaluation::~StaticEvaluation(void)
	{
	}

	int StaticEvaluation::PlayingFase(const RelativeCell& it)
	{
		int score = 0;
		if(it.IsMaxPiece()) { //friendly: max
			score += CalculateMovePhase(it);
		} else {
			score -= CalculateMovePhase(it);
		}
		
		return score;
	}

	int StaticEvaluation::CalculateMovePhase(const RelativeCell& it)
	{
		int score = 0;
		if ((it.GetData() & IsFlipped) == IsFlipped) {
			score += _flippedValue;

		}
		if (_board->CountNonDiagonalEdges(it) == 2) {
			score += _cornerValue;
		} else if (_board->CountNonDiagonalEdges(it) <= 2) {
			score += _blockedTileValue;
		}

		//check left/right
		bool tmpBool = false;
		if ((it.GetLeft().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
			score += _neighborValue;
			tmpBool = true;
		}
		if ((it.GetRight().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
			if (tmpBool) {
				score -= _neighborValue;
				score += _lineValue;
			}
			else { score += _neighborValue; }
		}

		//check up/down
		tmpBool = false;
		if ((it.GetTop().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
			score += _neighborValue;
			tmpBool = true;
		}
		if ((it.GetBottom().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
			if (tmpBool) {
				score -= _neighborValue;
				score += _lineValue;
			}
			else { score += _neighborValue; }
		}

		//check upleft/downright
		tmpBool = false;
		if ((it.GetTop().GetLeft().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
			score += _neighborValue;
			tmpBool = true;
		}
		if ((it.GetBottom().GetRight().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
			if (tmpBool) {
				score -= _neighborValue;
				score += _lineValue;
			}
			else { score += _neighborValue; }
		}

		//check upright/downleft
		tmpBool = false;
		if ((it.GetTop().GetRight().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
			score += _neighborValue;
			tmpBool = true;
		}
		if ((it.GetBottom().GetLeft().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
			if (tmpBool) {
				score -= _neighborValue;
				score += _lineValue;
			}
			else { score += _neighborValue; }
		}

		return score;
	}
	int StaticEvaluation::PlacingFase(const RelativeCell& it)
	{
		int score = 0;
		if(it.IsMaxPiece()) { //friendly
			score += CalculatePlacing(it);
		} else {
			score -= CalculatePlacing(it);
		}

		return score;
	}

	int StaticEvaluation::CalculatePlacing(const RelativeCell& it)
	{
		int score = 0;
		if ((it.GetAbsolutePosition().X() == 2 && it.GetAbsolutePosition().Y() == 1) || (it.GetAbsolutePosition().X() == 2 && it.GetAbsolutePosition().Y() == 2)) {
			score += _centerValue;
		} else if (it.GetSurroundingCells().size() == 0) {
			score += _semiCenterValue;
		} else if (it.GetAbsolutePosition().X() == 2) {
			score += _centerColumnValue;
		} else if ((it.GetLeft().GetData() & HasTile) == HasTile && (it.GetRight().GetData() & HasTile) == HasTile) {
			score += _bottomOrTopRowValue;;
		} else if (_board->CountNonDiagonalEdges(it) == 2) {
			score += _cornerValue2;
		}

		return score;
	}


	int StaticEvaluation::Eval(IBoard* board, Players players)
	{
		_board = board;
		vector<RelativeCell>* tiles = board->GetOccupiedTiles();

		int score = 0;

		for(auto it = tiles->begin(); it != tiles->end(); ++it) {
			if (tiles->size() == 12) {
				// static evaluation for the playing face
				score += PlayingFase(*it);
			} else {
				// static evaluation for the piece placing face
				score += PlacingFase(*it);
			}
		}

		delete tiles;

		return score;
	}
}
