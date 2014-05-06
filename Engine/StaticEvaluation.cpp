#include "StaticEvaluation.h"

namespace engine {
	StaticEvaluation::StaticEvaluation(void)
	{
		_flippedValue = 10;
		_blockedTileValue = 8;
		_cornerValue = 9;
		_neighborValue = 11;
		_lineValue = 21;
	}

	StaticEvaluation::~StaticEvaluation(void)
	{
	}

	int StaticEvaluation::Eval(IBoard* board, Players players)
	{
		return rand();
		vector<Cell<int>>* tiles = board->GetOccupiedTiles();

		int score = 0;

		for(auto it = tiles->begin(); it != tiles->end(); ++it) {
			if((it->GetData() & IsMax) == IsMax && players == Max) { //friendly: max
				if ((it->GetData() & IsFlipped) == IsFlipped) {
					score += _flippedValue;

					if (board->GetNumberOfEdges(&*it) == 2) {
						score += _cornerValue;
					} else if (board->GetNumberOfEdges(&*it) <= 2) {
						score += _blockedTileValue;
					}

					//check left/right
					bool tmpBool = false;
					if ((it->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						score += _neighborValue;
						tmpBool = true;
					}
					if ((it->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						if (tmpBool) {
							score -= _neighborValue;
							score += _lineValue;
						}
						else { score += _neighborValue; }
					}

					//check up/down
					tmpBool = false;
					if ((it->GetTop()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						score += _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						if (tmpBool) {
							score -= _neighborValue;
							score += _lineValue;
						}
						else { score += _neighborValue; }
					}

					//check upleft/downright
					tmpBool = false;
					if ((it->GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						score += _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						if (tmpBool) {
							score -= _neighborValue;
							score += _lineValue;
						}
						else { score += _neighborValue; }
					}

					//check upright/downleft
					tmpBool = false;
					if ((it->GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						score += _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						if (tmpBool) {
							score -= _neighborValue;
							score += _lineValue;
						}
						else { score += _neighborValue; }
					}
				}
			} else if((it->GetData() & IsMax) != IsMax && players == Min) { //friendly: min
				if ((it->GetData() & IsFlipped) == IsFlipped) {
					score += _flippedValue;

					if (board->GetNumberOfEdges(&*it) == 2) {
						score += _cornerValue;
					} else if (board->GetNumberOfEdges(&*it) <= 2) {
						score += _blockedTileValue;
					}

					//check left/right
					bool tmpBool = false;
					if ((it->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						score += _neighborValue;
						tmpBool = true;
					}
					if ((it->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						if (tmpBool) {
							score -= _neighborValue;
							score += _lineValue;
						}
						else { score += _neighborValue; }
					}

					//check up/down
					tmpBool = false;
					if ((it->GetTop()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						score += _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						if (tmpBool) {
							score -= _neighborValue;
							score += _lineValue;
						}
						else { score += _neighborValue; }
					}

					//check upleft/downright
					tmpBool = false;
					if ((it->GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						score += _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						if (tmpBool) {
							score -= _neighborValue;
							score += _lineValue;
						}
						else { score += _neighborValue; }
					}

					//check upright/downleft
					tmpBool = false;
					if ((it->GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						score += _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						if (tmpBool) {
							score -= _neighborValue;
							score += _lineValue;
						}
						else { score += _neighborValue; }
					}
				}
			} else if((it->GetData() & IsMax) != IsMax && players == Max) { //hostile: min
				if ((it->GetData() & IsFlipped) == IsFlipped) {
					score -= _flippedValue;

					if (board->GetNumberOfEdges(&*it) == 2) {
						score -= _cornerValue;
					} else if (board->GetNumberOfEdges(&*it) <= 2) {
						score -= _blockedTileValue;
					}

					//check left/right
					bool tmpBool = false;
					if ((it->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						score -= _neighborValue;
						tmpBool = true;
					}
					if ((it->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						if (tmpBool) {
							score += _neighborValue;
							score -= _lineValue;
						}
						else { score -= _neighborValue; }
					}

					//check up/down
					tmpBool = false;
					if ((it->GetTop()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						score -= _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						if (tmpBool) {
							score += _neighborValue;
							score -= _lineValue;
						}
						else { score -= _neighborValue; }
					}

					//check upleft/downright
					tmpBool = false;
					if ((it->GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						score -= _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						if (tmpBool) {
							score += _neighborValue;
							score -= _lineValue;
						}
						else { score -= _neighborValue; }
					}

					//check upright/downleft
					tmpBool = false;
					if ((it->GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						score -= _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
						if (tmpBool) {
							score += _neighborValue;
							score -= _lineValue;
						}
						else { score -= _neighborValue; }
					}
				}
			} else if((it->GetData() & IsMax) == IsMax && players == Min) { //hostile: max
				if ((it->GetData() & IsFlipped) == IsFlipped) {
					score -= _flippedValue;

					if (board->GetNumberOfEdges(&*it) == 2) {
						score -= _cornerValue;
					} else if (board->GetNumberOfEdges(&*it) <= 2) {
						score -= _blockedTileValue;
					}

					//check left/right
					bool tmpBool = false;
					if ((it->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						score -= _neighborValue;
						tmpBool = true;
					}
					if ((it->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						if (tmpBool) {
							score += _neighborValue;
							score -= _lineValue;
						}
						else { score -= _neighborValue; }
					}

					//check up/down
					tmpBool = false;
					if ((it->GetTop()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						score -= _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						if (tmpBool) {
							score += _neighborValue;
							score -= _lineValue;
						}
						else { score -= _neighborValue; }
					}

					//check upleft/downright
					tmpBool = false;
					if ((it->GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						score -= _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						if (tmpBool) {
							score += _neighborValue;
							score -= _lineValue;
						}
						else { score -= _neighborValue; }
					}

					//check upright/downleft
					tmpBool = false;
					if ((it->GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						score -= _neighborValue;
						tmpBool = true;
					}
					if ((it->GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
						if (tmpBool) {
							score += _neighborValue;
							score -= _lineValue;
						}
						else { score -= _neighborValue; }
					}
				}
			}
		}

		delete(tiles);

		return score;
	}
}
