#include "stdafx.h"
#include "BoardWrapper.h"


namespace engine {
namespace wrapper {
	BoardWrapper::BoardWrapper(void)
	{
		_board = new Board();
	}

	BoardWrapper::~BoardWrapper(void)
	{
		delete _board;
	}

	void BoardWrapper::ExecuteMove(MoveWrapper^ mw, engine::wrapper::Players player) {
		Move* mv = WrapperConversionUtility().ConvertMove(mw);
		_board->ExecuteMove(mv, static_cast<engine::Players>(player));
	}

	List<TileWrapper^>^ BoardWrapper::GetOccupiedTiles() {
		vector<Tile<int>>* native = _board->GetOccupiedTiles();
		List<TileWrapper^> ^wrapped = gcnew List<TileWrapper^>();

		for(unsigned i = 0; i < native->size(); i++) {
			wrapped->Add(WrapperConversionUtility().ConvertTile(native->at(i)));
		}
		return wrapped;
	}

	TileWrapper^ BoardWrapper::GetRelativeTileAt(Vector2DWrapper^ relativePosition) {
		Vector2D* position = WrapperConversionUtility().ConvertVector2D(relativePosition);
		Tile<int>* relativeTileAt = _board->GetRelativeTileAt(*position);
		return WrapperConversionUtility().ConvertTile(relativeTileAt);
	}
}
}
