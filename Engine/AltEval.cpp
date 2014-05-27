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
		score += CalcRightScore(cell, player);
		score += CalcDownScore(cell, player);
		score += CalcDownRightScore(cell, player);
		score += CalcTopRightScore(cell, player);
		return score;
	}

	int AltEval::CalcRightScore(RelativeCell &cell, Players player) {
		int score = 0;
		// Right
		RelativeCell current = cell;
		for (int i = 0; i < 3; i++) {
			if (current.HasTile() && current.GetPlayer() == player && current.IsFlipped()) {
				score += score + 10;
				if (current.IsFlipped()) {
					score += 50;
				}
			}
			current = current.GetRight();
		}

		// Left
		current = cell;
		for (int i = 0; i < 3; i++) {
			if (current.HasTile() && current.GetPlayer() == player && current.IsFlipped()) {
				score += score + 10;
				if (current.IsFlipped()) {
					score += 50;
				}
			}
			current = current.GetLeft();
		}
		return score;
	}

	int AltEval::CalcDownScore(RelativeCell &cell, Players player) {
		int score = 0;
		// Right
		RelativeCell current = cell;
		for (int i = 0; i < 3; i++) {
			if (current.HasTile() && current.GetPlayer() == player) {
				score += score + 10;
				if (current.IsFlipped()) {
					score += 50;
				}
			}
			current = current.GetBottom();
		}

		// Left
		current = cell;
		for (int i = 0; i < 3; i++) {
			if (current.HasTile() && current.GetPlayer() == player && current.IsFlipped()) {
				score += score + 10;
				if (current.IsFlipped()) {
					score += 50;
				}
			}
			current = current.GetBottom();
		}
		return score;
	}

	int AltEval::CalcDownRightScore(RelativeCell &cell, Players player) {
		int score = 0;
		// Right
		RelativeCell current = cell;
		for (int i = 0; i < 3; i++) {
			if (current.HasTile() && current.GetPlayer() == player && current.IsFlipped()) {
				score += score + 10;
				if (current.IsFlipped()) {
					score += 50;
				}
			}
			current = current.GetBottom().GetRight();
		}

		// Left
		current = cell;
		for (int i = 0; i < 3; i++) {
			if (current.HasTile() && current.GetPlayer() == player && current.IsFlipped()) {
				score += score + 10;
				if (current.IsFlipped()) {
					score += 50;
				}
			}
			current = current.GetBottom().GetRight();
		}
		return score;
	}

	int AltEval::CalcTopRightScore(RelativeCell &cell, Players player) {
		int score = 0;
		// Right
		RelativeCell current = cell;
		for (int i = 0; i < 3; i++) {
			if (current.HasTile() && current.GetPlayer() == player && current.IsFlipped()) {
				score += score + 10;
				if (current.IsFlipped()) {
					score += 50;
				}
			}
			current = current.GetTop().GetRight();
		}

		// Left
		current = cell;
		for (int i = 0; i < 3; i++) {
			if (current.HasTile() && current.GetPlayer() == player && current.IsFlipped()) {
				score += score + 10;
				if (current.IsFlipped()) {
					score += 50;
				}
			}
			current = current.GetTop().GetRight();
		}
		return score;
	}

	const RelativeCell &AltEval::GetLeft(RelativeCell &current) {
		return current.GetLeft();
	}

	const RelativeCell &AltEval::GetRight(RelativeCell &current) {
		return current.GetRight();
	}

	const RelativeCell &AltEval::GetTop(RelativeCell &current) {
		return current.GetTop();
	}

	const RelativeCell &AltEval::GetBottom(RelativeCell &current) {
		return current.GetBottom();
	}

	const RelativeCell &AltEval::GetTopLeft(RelativeCell &current) {
		return current.GetTop().GetLeft();
	}

	const RelativeCell &AltEval::GetTopRight(RelativeCell &current) {
		return current.GetTop().GetRight();
	}

	const RelativeCell &AltEval::GetBottomLeft(RelativeCell &current) {
		return current.GetBottom().GetLeft();
	}

	const RelativeCell &AltEval::GetBottomRight(RelativeCell &current) {
		return current.GetBottom().GetRight();
	}
}