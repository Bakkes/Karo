#include "stdafx.h"
#include "MoveWrapper.h"
#include "WrapperConversionUtility.h"

namespace engine {
namespace wrapper {

	MoveWrapper::MoveWrapper(MoveType moveType, Vector2D fromTile, Vector2D toTile, Vector2D usedTile) {
		_move = new engine::Move(static_cast<engine::MoveType>(moveType), fromTile, toTile, usedTile);
	}

	MoveWrapper::~MoveWrapper() {
		delete _move;
	}

	engine::wrapper::MoveType MoveWrapper::GetMoveType() {
		return static_cast<engine::wrapper::MoveType>(_move->GetMoveType());
	}

	engine::wrapper::Vector2DWrapper^ MoveWrapper::GetFromTile() {
		return WrapperConversionUtility::ConvertVector2D(_move->GetFromTile());
	}

	engine::wrapper::Vector2DWrapper^ MoveWrapper::GetToTile() {
		return WrapperConversionUtility::ConvertVector2D(_move->GetToTile());
	}

	void MoveWrapper::SetToTile(engine::wrapper::Vector2DWrapper^ location) {
		_move->SetToTile(WrapperConversionUtility::ConvertVector2DStack(location));
	}

	engine::wrapper::Vector2DWrapper^ MoveWrapper::GetUsedTile() {
		return WrapperConversionUtility::ConvertVector2D(_move->GetUsedTile());
	}

	bool MoveWrapper::HasUsedTile() {
		return _move->HasUsedTile();
	}

}
}