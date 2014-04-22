#include "stdafx.h"
#include "MoveWrapper.h"
#include "WrapperConversionUtility.h"

namespace engine {
namespace wrapper {

	MoveWrapper::MoveWrapper(MoveType moveType, Vector2D fromCell, Vector2D toCell, Vector2D usedCell) {
		_move = new engine::Move(static_cast<engine::MoveType>(moveType), fromCell, toCell, usedCell);
	}

	MoveWrapper::~MoveWrapper() {
		delete _move;
	}

	engine::wrapper::MoveType MoveWrapper::GetMoveType() {
		return static_cast<engine::wrapper::MoveType>(_move->GetMoveType());
	}

	engine::wrapper::Vector2DWrapper^ MoveWrapper::GetFromCell() {
		return WrapperConversionUtility::ConvertVector2D(_move->GetFromCell());
	}

	engine::wrapper::Vector2DWrapper^ MoveWrapper::GetToCell() {
		return WrapperConversionUtility::ConvertVector2D(_move->GetToCell());
	}

	engine::wrapper::Vector2DWrapper^ MoveWrapper::GetUsedCell() {
		return WrapperConversionUtility::ConvertVector2D(_move->GetUsedCell());
	}

	bool MoveWrapper::HasUsedCell() {
		return _move->HasUsedCell();
	}

}
}