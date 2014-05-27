#include "AltEval.h"

namespace engine {
	AltEval::AltEval(void) {
	}

	AltEval::~AltEval(void) {
	}

	int AltEval::Eval(IBoard* board, Players player) {
		std::vector<RelativeCell>* tiles = board->GetOccupiedTiles();
		int scoreMax = 0;
		int scoreMin = 0;
		for (auto it = tiles->begin(); it != tiles->end(); ++it) {
			scoreMax += CalcScoreFor(*it, Max);
			scoreMin += CalcScoreFor(*it, Min);
		}
		return scoreMax - scoreMin;
	}

	int AltEval::CalcScoreFor(RelativeCell &cell, Players player) {
		int score = 0;
		score += CalcScoreWithNext(cell, player, &AltEval::GetLeft);
		score += CalcScoreWithNext(cell, player, &AltEval::GetRight);
		score += CalcScoreWithNext(cell, player, &AltEval::GetTop);
		score += CalcScoreWithNext(cell, player, &AltEval::GetBottom);

		score += CalcScoreWithNext(cell, player, &AltEval::GetTopLeft);
		score += CalcScoreWithNext(cell, player, &AltEval::GetTopRight);
		score += CalcScoreWithNext(cell, player, &AltEval::GetBottomLeft);
		score += CalcScoreWithNext(cell, player, &AltEval::GetBottomRight);
		return score;
	}

	int AltEval::CalcScoreWithNext(RelativeCell &cell, Players player,
		const RelativeCell(AltEval::*GetNext)(RelativeCell&)) {
		int score = 0;
		// Right
		RelativeCell current = cell;
		for (int i = 0; i < 3; i++) {
			if(!current.HasTile()){
				continue;
			}
			if(current.IsEmpty()){
				continue;
			}
			if(current.GetPlayer() != player){
				continue;
			}
			score += 10;
			if (current.IsFlipped()) {
				score *= 3;
			}
			current = (*this.*GetNext)(current);
		}
		return score;
	}

	const RelativeCell AltEval::GetLeft(RelativeCell &current) {
		return current.GetLeft();
	}

	const RelativeCell AltEval::GetRight(RelativeCell &current) {
		return current.GetRight();
	}

	const RelativeCell AltEval::GetTop(RelativeCell &current) {
		return current.GetTop();
	}

	const RelativeCell AltEval::GetBottom(RelativeCell &current) {
		return current.GetBottom();
	}

	const RelativeCell AltEval::GetTopLeft(RelativeCell &current) {
		return current.GetTop().GetLeft();
	}

	const RelativeCell AltEval::GetTopRight(RelativeCell &current) {
		return current.GetTop().GetRight();
	}

	const RelativeCell AltEval::GetBottomLeft(RelativeCell &current) {
		return current.GetBottom().GetLeft();
	}

	const RelativeCell AltEval::GetBottomRight(RelativeCell &current) {
		return current.GetBottom().GetRight();
	}
}