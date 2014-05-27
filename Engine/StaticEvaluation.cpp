#include "StaticEvaluation.h"

namespace engine {
	StaticEvaluation::StaticEvaluation(void)
	{
		_flippedValue = 25;
		_blockedTileValue = -50;
		_cornerValue = -100;
		_neighborValue = 150;
		_lineValue = 1500;

		_centerValue = 5;
		_semiCenterValue = 4;
		_centerColumnValue = 3;
		_bottomOrTopRowValue = 2;
		_cornerValue2 = 1;
	}

	StaticEvaluation::~StaticEvaluation(void)
	{
	}

	int StaticEvaluation::PlayingPhase(int score, IBoard* board, RelativeCell it, Players players)
	{
		if((it.GetData() & IsMax) == IsMax && players == Max) { //friendly: max
			score = PlayingPhaseFriendlyMax(score, board, it, players);
		} else if((it.GetData() & IsMax) != IsMax && players == Min) { //friendly: min
			score = PlayingPhaseFriendlyMin(score, board, it, players);
		} else if((it.GetData() & IsMax) != IsMax && players == Max) { //hostile: min
			score = PlayingPhaseHostileMin(score, board, it, players);
		} else if((it.GetData() & IsMax) == IsMax && players == Min) { //hostile: max
			score = PlayingPhaseHostileMax(score, board, it, players);
		}
		
		return score;
	}

	int StaticEvaluation::PlayingPhaseFriendlyMax(int score, IBoard* board, RelativeCell it, Players players)
	{
		if ((it.GetData() & IsFlipped) == IsFlipped) {
			score += _flippedValue;

			if (board->CountNonDiagonalEdges(it) == 2) {
				score += _cornerValue;
			} else if (board->CountNonDiagonalEdges(it) <= 2) {
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
		}

		return score;
	}

	int StaticEvaluation::PlayingPhaseFriendlyMin(int score, IBoard* board, RelativeCell it, Players players)
	{
		if ((it.GetData() & IsFlipped) == IsFlipped) {
			score += _flippedValue;

			if (board->CountNonDiagonalEdges(it) == 2) {
				score += _cornerValue;
			} else if (board->CountNonDiagonalEdges(it) <= 2) {
				score += _blockedTileValue;
			}

			//check left/right
			bool tmpBool = false;
			if ((it.GetLeft().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetRight().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}

			//check up/down
			tmpBool = false;
			if ((it.GetTop().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}

			//check upleft/downright
			tmpBool = false;
			if ((it.GetTop().GetLeft().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom().GetRight().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}

			//check upright/downleft
			tmpBool = false;
			if ((it.GetTop().GetRight().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom().GetLeft().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}
		}

		return score;
	}

	int StaticEvaluation::PlayingPhaseHostileMin(int score, IBoard* board, RelativeCell it, Players players)
	{
		if ((it.GetData() & IsFlipped) == IsFlipped) {
			score -= _flippedValue;

			if (board->CountNonDiagonalEdges(it) == 2) {
				score -= _cornerValue;
			} else if (board->CountNonDiagonalEdges(it) <= 2) {
				score -= _blockedTileValue;
			}

			//check left/right
			bool tmpBool = false;
			if ((it.GetLeft().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetRight().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check up/down
			tmpBool = false;
			if ((it.GetTop().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check upleft/downright
			tmpBool = false;
			if ((it.GetTop().GetLeft().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom().GetRight().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check upright/downleft
			tmpBool = false;
			if ((it.GetTop().GetRight().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom().GetLeft().GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}
		}

		return score;
	}

	int StaticEvaluation::PlayingPhaseHostileMax(int score, IBoard* board, RelativeCell it, Players players)
	{
		if ((it.GetData() & IsFlipped) == IsFlipped) {
			score -= _flippedValue;

			if (board->CountNonDiagonalEdges(it) == 2) {
				score -= _cornerValue;
			} else if (board->CountNonDiagonalEdges(it) <= 2) {
				score -= _blockedTileValue;
			}

			//check left/right
			bool tmpBool = false;
			if ((it.GetLeft().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetRight().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check up/down
			tmpBool = false;
			if ((it.GetTop().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check upleft/downright
			tmpBool = false;
			if ((it.GetTop().GetLeft().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom().GetRight().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check upright/downleft
			tmpBool = false;
			if ((it.GetTop().GetRight().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom().GetLeft().GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}
		}

		return score;
	}

	int StaticEvaluation::PlacingPhase(int score, IBoard* board, RelativeCell it, Players players)
	{
		if(((it.GetData() & IsMax) == IsMax && players == Max) || ((it.GetData() & IsMax) != IsMax && players == Min)) { //friendly
			score = PlacingPhaseFriendly(score, board, it, players);
		} else if(((it.GetData() & IsMax) == IsMax && players == Min) || ((it.GetData() & IsMax) != IsMax && players == Max)) { //hostile
			score = PlacingPhaseHostile(score, board, it, players);
		}

		return score;
	}

	int StaticEvaluation::PlacingPhaseFriendly(int score, IBoard* board, RelativeCell it, Players players)
	{
		if ((it.GetAbsolutePosition().X() == 2 && it.GetAbsolutePosition().Y() == 1) || (it.GetAbsolutePosition().X() == 2 && it.GetAbsolutePosition().Y() == 2)) {
			score += _centerValue;
		} else if (it.GetSurroundingCells().size() == 0) {
			score += _semiCenterValue;
		} else if (it.GetAbsolutePosition().X() == 2) {
			score += _centerColumnValue;
		} else if ((it.GetLeft().GetData() & HasTile) == HasTile && (it.GetRight().GetData() & HasTile) == HasTile) {
			score += _bottomOrTopRowValue;;
		} else if (board->CountNonDiagonalEdges(it) == 2) {
			score += _cornerValue2;
		}

		return score;
	}

	int StaticEvaluation::PlacingPhaseHostile(int score, IBoard* board, RelativeCell it, Players players)
	{
		if ((it.GetAbsolutePosition().X() == 2 && it.GetAbsolutePosition().Y() == 1) || (it.GetAbsolutePosition().X() == 2 && it.GetAbsolutePosition().Y() == 2)) {
			score -= _centerValue;
		} else if (it.GetSurroundingCells().size() == 0) {
			score -= _semiCenterValue;
		} else if (it.GetAbsolutePosition().X() == 2) {
			score -= _centerColumnValue;
		} else if ((it.GetLeft().GetData() & HasTile) == HasTile && (it.GetRight().GetData() & HasTile) == HasTile) {
			score -= _bottomOrTopRowValue;
		} else if (board->CountNonDiagonalEdges(it) == 2) {
			score -= _cornerValue2;
		}

		return score;
	}

	int StaticEvaluation::Eval(IBoard* board, Players players)
	{
		vector<RelativeCell>* tiles = board->GetOccupiedTiles();

		int score = 0;

		for(auto it = tiles->begin(); it != tiles->end(); ++it) {
			if (tiles->size() == 12) {
				// static evaluation for the playing face
				score = PlayingPhase(score, board, *it, players);
			} else {
				// static evaluation for the piece placing face
				score = PlacingPhase(score, board, *it, players);
			}
		}

		delete tiles;

		return score;
	}
}
