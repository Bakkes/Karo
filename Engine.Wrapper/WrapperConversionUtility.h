#pragma once

#include "Move.h"
#include "MoveWrapper.h"

namespace engine {
namespace wrapper{

class WrapperConversionUtility {
public:
	static Move* ConvertMove(MoveWrapper^ moveWrapper) {
		return new engine::Move(static_cast<engine::MoveType>(moveWrapper->GetMoveType()), 
			moveWrapper->GetFromTile(), moveWrapper->GetToTile(), 
			static_cast<engine::MoveDirection>(moveWrapper->GetMoveDirection()), moveWrapper->GetEmptyTile());
	}

	static MoveWrapper^ ConvertMove(Move* move) {
		return gcnew MoveWrapper(static_cast<engine::wrapper::MoveType>(move->GetMoveType()), 
			move->GetFromTile(), move->GetToTile(), static_cast<engine::wrapper::MoveDirection>(move->GetMoveDirection()), 
			move->GetEmptyTile());;
	}
};

}
}