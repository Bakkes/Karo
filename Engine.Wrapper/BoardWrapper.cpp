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
		_board->ExecuteMove(*WrapperConversionUtility().ConvertMove(mw), static_cast<engine::Players>(player));
	}

	List<CellWrapper^>^ BoardWrapper::GetOccupiedCells() {
		vector<RelativeCell>* native = _board->GetOccupiedTiles();
		List<CellWrapper^> ^wrapped = gcnew List<CellWrapper^>();

		for(unsigned i = 0; i < native->size(); i++) {
			wrapped->Add(WrapperConversionUtility().ConvertCell(native->at(i)));
		}
		return wrapped;
	}

	IEnumerable<MoveWrapper^>^ BoardWrapper::GetLegalMoves(Players player)
	{
		List<MoveWrapper^>^ managedMoves = gcnew List<MoveWrapper^>();
		vector<Move> nativeMoves = _board->GetLegalMoves(static_cast<engine::Players>(player));

		for (auto it = nativeMoves.begin(); it != nativeMoves.end(); ++it)
		{
			managedMoves->Add(WrapperConversionUtility::ConvertMove(*it));
		}
		
		return managedMoves;

	}

	CellWrapper^ BoardWrapper::GetRelativeCellAt(Vector2DWrapper^ relativePosition) {
		Vector2D* position = WrapperConversionUtility().ConvertVector2D(relativePosition);
		RelativeCell relativeCellAt = _board->GetRelativeCellAt(*position);
		return WrapperConversionUtility().ConvertCell(relativeCellAt);
	}

	void BoardWrapper::LoadFromString(String^ boardString, int topLeftX, int topLeftY) {
		delete _board;

		std::string stdBoardString = "";
		for (int i = 0; i < boardString->Length; ++i) {
			stdBoardString += (char) boardString[i];
		}

		_board = Board::CreateBoard(stdBoardString, Vector2D(topLeftX, topLeftY));
	}

	Board* BoardWrapper::GetInternalBoard() {
		return _board;
	}

	String^ BoardWrapper::ToString() {
		return gcnew String(_board->ToString().c_str());
	}
}
}
