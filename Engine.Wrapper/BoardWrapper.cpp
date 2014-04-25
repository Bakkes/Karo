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

	List<CellWrapper^>^ BoardWrapper::GetOccupiedCells() {
		vector<Cell<int>>* native = _board->GetOccupiedTiles();
		List<CellWrapper^> ^wrapped = gcnew List<CellWrapper^>();

		for(unsigned i = 0; i < native->size(); i++) {
			wrapped->Add(WrapperConversionUtility().ConvertCell(native->at(i)));
		}
		return wrapped;
	}

	IEnumerable<MoveWrapper^>^ BoardWrapper::GetLegalMoves(Players player)
	{
		List<MoveWrapper^>^ managedMoves = gcnew List<MoveWrapper^>();
		vector<Move>* nativeMoves = _board->GetLegalMoves(static_cast<engine::Players>(player));

		for (auto it = nativeMoves->begin(); it != nativeMoves->end(); ++it)
		{
			managedMoves->Add(WrapperConversionUtility::ConvertMove(*it));
		}
		return managedMoves;
	}

	CellWrapper^ BoardWrapper::GetRelativeCellAt(Vector2DWrapper^ relativePosition) {
		Vector2D* position = WrapperConversionUtility().ConvertVector2D(relativePosition);
		Cell<int>* relativeCellAt = _board->GetRelativeCellAt(*position);
		return WrapperConversionUtility().ConvertCell(relativeCellAt);
	}

	Board* BoardWrapper::GetInternalBoard() {
		return _board;
	}
}
}
