#include "StaticEvaluation.h"

namespace engine {
	StaticEvaluation::StaticEvaluation(void)
	{
		flippedValue = 10;
		blockedTileValue = 8;
		cornerValue = 9;
		neighborValue = 11;
		lineValue = 21;

		centerValue = 5;
		semiCenterValue = 4;
		centerColumnValue = 3;
		bottomOrTopRowValue = 2;
		cornerValue = 1;
	}

	StaticEvaluation::~StaticEvaluation(void)
	{
	}

	int StaticEvaluation::Eval(IBoard* board, Players players)
	{
		vector<Cell<int>>* tiles = board->GetOccupiedTiles();

		int score = 0;

		for(auto it = tiles->begin(); it != tiles->end(); ++it) {
			if (tiles->size() == 12) {
				  //****************************************//
				 // static evaluation for the playing face //
				//****************************************//

				if((*it->GetData() & IsMax) == IsMax && players == Max) { //friendly: max
					if ((*it->GetData() & IsFlipped) == IsFlipped) {
						score += flippedValue;

						if (board->GetNumberOfEdges(&*it) == 2) {
							score += cornerValue;
						} else if (board->GetNumberOfEdges(&*it) <= 2) {
							score += blockedTileValue;
						}

						//check left/right
						bool tmpBool = false;
						if ((*it->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							score += neighborValue;
							tmpBool = true;
						}
						if ((*it->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							if (tmpBool) {
								score -= neighborValue;
								score += lineValue;
							}
							else { score += neighborValue; }
						}

						//check up/down
						tmpBool = false;
						if ((*it->GetTop()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							score += neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							if (tmpBool) {
								score -= neighborValue;
								score += lineValue;
							}
							else { score += neighborValue; }
						}

						//check upleft/downright
						tmpBool = false;
						if ((*it->GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							score += neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							if (tmpBool) {
								score -= neighborValue;
								score += lineValue;
							}
							else { score += neighborValue; }
						}

						//check upright/downleft
						tmpBool = false;
						if ((*it->GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							score += neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							if (tmpBool) {
								score -= neighborValue;
								score += lineValue;
							}
							else { score += neighborValue; }
						}
					}
				} else if((*it->GetData() & IsMax) != IsMax && players == Min) { //friendly: min
					if ((*it->GetData() & IsFlipped) == IsFlipped) {
						score += flippedValue;

						if (board->GetNumberOfEdges(&*it) == 2) {
							score += cornerValue;
						} else if (board->GetNumberOfEdges(&*it) <= 2) {
							score += blockedTileValue;
						}

						//check left/right
						bool tmpBool = false;
						if ((*it->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							score += neighborValue;
							tmpBool = true;
						}
						if ((*it->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							if (tmpBool) {
								score -= neighborValue;
								score += lineValue;
							}
							else { score += neighborValue; }
						}

						//check up/down
						tmpBool = false;
						if ((*it->GetTop()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							score += neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							if (tmpBool) {
								score -= neighborValue;
								score += lineValue;
							}
							else { score += neighborValue; }
						}

						//check upleft/downright
						tmpBool = false;
						if ((*it->GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							score += neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							if (tmpBool) {
								score -= neighborValue;
								score += lineValue;
							}
							else { score += neighborValue; }
						}

						//check upright/downleft
						tmpBool = false;
						if ((*it->GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							score += neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							if (tmpBool) {
								score -= neighborValue;
								score += lineValue;
							}
							else { score += neighborValue; }
						}
					}
				} else if((*it->GetData() & IsMax) != IsMax && players == Max) { //hostile: min
					if ((*it->GetData() & IsFlipped) == IsFlipped) {
						score -= flippedValue;

						if (board->GetNumberOfEdges(&*it) == 2) {
							score -= cornerValue;
						} else if (board->GetNumberOfEdges(&*it) <= 2) {
							score -= blockedTileValue;
						}

						//check left/right
						bool tmpBool = false;
						if ((*it->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							score -= neighborValue;
							tmpBool = true;
						}
						if ((*it->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							if (tmpBool) {
								score += neighborValue;
								score -= lineValue;
							}
							else { score -= neighborValue; }
						}

						//check up/down
						tmpBool = false;
						if ((*it->GetTop()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							score -= neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							if (tmpBool) {
								score += neighborValue;
								score -= lineValue;
							}
							else { score -= neighborValue; }
						}

						//check upleft/downright
						tmpBool = false;
						if ((*it->GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							score -= neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							if (tmpBool) {
								score += neighborValue;
								score -= lineValue;
							}
							else { score -= neighborValue; }
						}

						//check upright/downleft
						tmpBool = false;
						if ((*it->GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							score -= neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == IsFlipped) {
							if (tmpBool) {
								score += neighborValue;
								score -= lineValue;
							}
							else { score -= neighborValue; }
						}
					}
				} else if((*it->GetData() & IsMax) == IsMax && players == Min) { //hostile: max
					if ((*it->GetData() & IsFlipped) == IsFlipped) {
						score -= flippedValue;

						if (board->GetNumberOfEdges(&*it) == 2) {
							score -= cornerValue;
						} else if (board->GetNumberOfEdges(&*it) <= 2) {
							score -= blockedTileValue;
						}

						//check left/right
						bool tmpBool = false;
						if ((*it->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							score -= neighborValue;
							tmpBool = true;
						}
						if ((*it->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							if (tmpBool) {
								score += neighborValue;
								score -= lineValue;
							}
							else { score -= neighborValue; }
						}

						//check up/down
						tmpBool = false;
						if ((*it->GetTop()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							score -= neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							if (tmpBool) {
								score += neighborValue;
								score -= lineValue;
							}
							else { score -= neighborValue; }
						}

						//check upleft/downright
						tmpBool = false;
						if ((*it->GetTop()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							score -= neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							if (tmpBool) {
								score += neighborValue;
								score -= lineValue;
							}
							else { score -= neighborValue; }
						}

						//check upright/downleft
						tmpBool = false;
						if ((*it->GetTop()->GetRight()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							score -= neighborValue;
							tmpBool = true;
						}
						if ((*it->GetBottom()->GetLeft()->GetData() & (IsMax | IsFlipped)) == (IsMax | IsFlipped)) {
							if (tmpBool) {
								score += neighborValue;
								score -= lineValue;
							}
							else { score -= neighborValue; }
						}
					}
				}
			} else {
				  //**********************************************//
				 // static evaluation for the piece placing face //
				//**********************************************//

				if(((*it->GetData() & IsMax) == IsMax && players == Max) || ((*it->GetData() & IsMax) != IsMax && players == Min)) { //friendly
					if ((it->GetPosition()->X() == 2 && it->GetPosition()->Y() == 1) || (it->GetPosition()->X() == 2 && it->GetPosition()->Y() == 2)) {
						score += centerValue;
					} else if (it->GetSurroundingCells().size() == 0) {
						score += semiCenterValue;
					} else if (it->GetPosition()->X() == 2) {
						score += centerColumnValue;
					} else if ((*it->GetLeft()->GetData() & HasCell) == HasCell && (*it->GetRight()->GetData() & HasCell) == HasCell) {
						score += bottomOrTopRowValue;;
					} else if (board->GetNumberOfEdges(&*it) == 2) {
						score += cornerValue;
					}
				} else if(((*it->GetData() & IsMax) == IsMax && players == Min) || ((*it->GetData() & IsMax) != IsMax && players == Max)) { //hostile
					if ((it->GetPosition()->X() == 2 && it->GetPosition()->Y() == 1) || (it->GetPosition()->X() == 2 && it->GetPosition()->Y() == 2)) {
						score -= centerValue;
					} else if (it->GetSurroundingCells().size() == 0) {
						score -= semiCenterValue;
					} else if (it->GetPosition()->X() == 2) {
						score -= centerColumnValue;
					} else if ((*it->GetLeft()->GetData() & HasCell) == HasCell && (*it->GetRight()->GetData() & HasCell) == HasCell) {
						score -= bottomOrTopRowValue;;
					} else if (board->GetNumberOfEdges(&*it) == 2) {
						score -= cornerValue;
					}
				}
			}
		}

		delete(tiles);

		return score;
	}
}
