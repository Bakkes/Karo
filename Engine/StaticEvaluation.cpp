#include "StaticEvaluation.h"

namespace engine {
	StaticEvaluation::StaticEvaluation(void)
	{
		_flippedValue = 10;
		_blockedTileValue = 8;
		_cornerValue = 9;
		_neighborValue = 11;
		_lineValue = 21;

		_centerValue = 5;
		_semiCenterValue = 4;
		_centerColumnValue = 3;
		_bottomOrTopRowValue = 2;
		_cornerValue = 1;
	}

	StaticEvaluation::~StaticEvaluation(void)
	{
	}

	int StaticEvaluation::PlayingFase(int score, IBoard* board, Cell<int> it, Players players)
	{
		if((it.GetData() & IsMax) == IsMax && players == Max) { //friendly: max
			PlayingFaseFriendlyMax(score, board, it, players);
		} else if((it.GetData() & IsMax) != IsMax && players == Min) { //friendly: min
			PlayingFaseFriendlyMin(score, board, it, players);
		} else if((it.GetData() & IsMax) != IsMax && players == Max) { //hostile: min
			PlayingFaseHostileMin(score, board, it, players);
		} else if((it.GetData() & IsMax) == IsMax && players == Min) { //hostile: max
			PlayingFaseHostileMax(score, board, it, players);
		}
		
		return score;
	}

	int StaticEvaluation::PlayingFaseFriendlyMax(int score, IBoard* board, Cell<int> it, Players players)
	{
		if ((it.GetData() & IsFlipped) == IsFlipped) {
			score += _flippedValue;

			if (board->CountNonDiagonalEdges(&it) == 2) {
				score += _cornerValue;
			} else if (board->CountNonDiagonalEdges(&it) <= 2) {
				score += _blockedTileValue;
			}

			//check left/right
			bool tmpBool = false;
			if ((it.GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}

			//check up/down
			tmpBool = false;
			if ((it.GetTop()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}

			//check upleft/downright
			tmpBool = false;
			if ((it.GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}

			//check upright/downleft
			tmpBool = false;
			if ((it.GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}
		}

		return score;
	}

	int StaticEvaluation::PlayingFaseFriendlyMin(int score, IBoard* board, Cell<int> it, Players players)
	{
		if ((it.GetData() & IsFlipped) == IsFlipped) {
			score += _flippedValue;

			if (board->CountNonDiagonalEdges(&it) == 2) {
				score += _cornerValue;
			} else if (board->CountNonDiagonalEdges(&it) <= 2) {
				score += _blockedTileValue;
			}

			//check left/right
			bool tmpBool = false;
			if ((it.GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}

			//check up/down
			tmpBool = false;
			if ((it.GetTop()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}

			//check upleft/downright
			tmpBool = false;
			if ((it.GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}

			//check upright/downleft
			tmpBool = false;
			if ((it.GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score += _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score -= _neighborValue;
					score += _lineValue;
				}
				else { score += _neighborValue; }
			}
		}

		return score;
	}

	int StaticEvaluation::PlayingFaseHostileMin(int score, IBoard* board, Cell<int> it, Players players)
	{
		if ((it.GetData() & IsFlipped) == IsFlipped) {
			score -= _flippedValue;

			if (board->CountNonDiagonalEdges(&it) == 2) {
				score -= _cornerValue;
			} else if (board->CountNonDiagonalEdges(&it) <= 2) {
				score -= _blockedTileValue;
			}

			//check left/right
			bool tmpBool = false;
			if ((it.GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check up/down
			tmpBool = false;
			if ((it.GetTop()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check upleft/downright
			tmpBool = false;
			if ((it.GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check upright/downleft
			tmpBool = false;
			if ((it.GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}
		}

		return score;
	}

	int StaticEvaluation::PlayingFaseHostileMax(int score, IBoard* board, Cell<int> it, Players players)
	{
		if ((it.GetData() & IsFlipped) == IsFlipped) {
			score -= _flippedValue;

			if (board->CountNonDiagonalEdges(&it) == 2) {
				score -= _cornerValue;
			} else if (board->CountNonDiagonalEdges(&it) <= 2) {
				score -= _blockedTileValue;
			}

			//check left/right
			bool tmpBool = false;
			if ((it.GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check up/down
			tmpBool = false;
			if ((it.GetTop()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check upleft/downright
			tmpBool = false;
			if ((it.GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}

			//check upright/downleft
			tmpBool = false;
			if ((it.GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				score -= _neighborValue;
				tmpBool = true;
			}
			if ((it.GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
				if (tmpBool) {
					score += _neighborValue;
					score -= _lineValue;
				}
				else { score -= _neighborValue; }
			}
		}

		return score;
	}

	int StaticEvaluation::PlacingFase(int score, IBoard* board, Cell<int> it, Players players)
	{
		if(((it.GetData() & IsMax) == IsMax && players == Max) || ((it.GetData() & IsMax) != IsMax && players == Min)) { //friendly
			PlacingFaseFriendly(score, board, it, players);
		} else if(((it.GetData() & IsMax) == IsMax && players == Min) || ((it.GetData() & IsMax) != IsMax && players == Max)) { //hostile
			PlacingFaseHostile(score, board, it, players);
		}

		return score;
	}

	int StaticEvaluation::PlacingFaseFriendly(int score, IBoard* board, Cell<int> it, Players players)
	{
		if ((it.GetPosition().X() == 2 && it.GetPosition().Y() == 1) || (it.GetPosition().X() == 2 && it.GetPosition().Y() == 2)) {
			score += _centerValue;
		} else if (it.GetSurroundingCells().size() == 0) {
			score += _semiCenterValue;
		} else if (it.GetPosition().X() == 2) {
			score += _centerColumnValue;
		} else if ((it.GetLeft()->GetData() & HasTile) == HasTile && (it.GetRight()->GetData() & HasTile) == HasTile) {
			score += _bottomOrTopRowValue;;
		} else if (board->CountNonDiagonalEdges(&it) == 2) {
			score += _cornerValue;
		}

		return score;
	}

	int StaticEvaluation::PlacingFaseHostile(int score, IBoard* board, Cell<int> it, Players players)
	{
		if ((it.GetPosition().X() == 2 && it.GetPosition().Y() == 1) || (it.GetPosition().X() == 2 && it.GetPosition().Y() == 2)) {
			score -= _centerValue;
		} else if (it.GetSurroundingCells().size() == 0) {
			score -= _semiCenterValue;
		} else if (it.GetPosition().X() == 2) {
			score -= _centerColumnValue;
		} else if ((it.GetLeft()->GetData() & HasTile) == HasTile && (it.GetRight()->GetData() & HasTile) == HasTile) {
			score -= _bottomOrTopRowValue;
		} else if (board->CountNonDiagonalEdges(&it) == 2) {
			score -= _cornerValue;
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
				score = PlayingFase(score, board, *it, players);
			} else {
				// static evaluation for the piece placing face
				score = PlacingFase(score, board, *it, players);
			}
		}

		delete tiles;

		return score;
	}
}
