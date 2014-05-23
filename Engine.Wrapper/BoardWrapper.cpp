#include "BoardWrapper.h"

namespace engine {
namespace wrapper {
	BoardWrapper::BoardWrapper(void)
	{
		_board = new Board();
		_legalMaxMoves = nullptr;
		_legalMinMoves = nullptr;
	}

	BoardWrapper::~BoardWrapper(void)
	{
		this->!BoardWrapper();
	}

	BoardWrapper::!BoardWrapper(void)
	{
		delete _board;
		_board = nullptr;
	}

	void BoardWrapper::ExecuteMove(MoveWrapper^ mw, engine::wrapper::Players player) {
		_legalMaxMoves = nullptr;
		_legalMinMoves = nullptr;
		Move* m = WrapperConversionUtility().ConvertMove(mw);
		_board->ExecuteMove(*m, static_cast<engine::Players>(player));
		delete m;
	}

	List<CellWrapper^>^ BoardWrapper::GetOccupiedCells() {
		vector<RelativeCell>* native = _board->GetOccupiedTiles();
		List<CellWrapper^> ^wrapped = gcnew List<CellWrapper^>();

		for(unsigned i = 0; i < native->size(); i++) {
			wrapped->Add(WrapperConversionUtility().ConvertCell(native->at(i)));
		}
		delete native;
		return wrapped;
	}

	IEnumerable<MoveWrapper^>^ BoardWrapper::GetLegalMoves(Players player)
	{
		// Return cached moves.
		if (player == Players::Max && _legalMaxMoves != nullptr) {
			return _legalMaxMoves;
		}
		if (player == Players::Min && _legalMinMoves != nullptr) {
			return _legalMinMoves;
		}
		List<MoveWrapper^>^ managedMoves = gcnew List<MoveWrapper^>();
		vector<Move> nativeMoves = _board->GetLegalMoves(static_cast<engine::Players>(player));

		for (auto it = nativeMoves.begin(); it != nativeMoves.end(); ++it)
		{
			managedMoves->Add(WrapperConversionUtility::ConvertMove(*it));
		}
		if (player == Players::Max) {
			_legalMaxMoves = managedMoves;
		}
		if (player == Players::Min) {
			_legalMinMoves = managedMoves;
		}
		return managedMoves;
	}

	CellWrapper^ BoardWrapper::GetRelativeCellAt(Vector2DWrapper^ relativePosition) {
		Vector2D* position = WrapperConversionUtility().ConvertVector2D(relativePosition);
		RelativeCell relativeCellAt = _board->GetRelativeCellAt(*position);
		delete position;
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

	Board* BoardWrapper::GetInternalBoardCopy() {
		return new Board(*_board);
	}

	Board* BoardWrapper::GetInternalBoard() {
		return _board;
	}

	String^ BoardWrapper::ToString() {
		return gcnew String(_board->ToString().c_str());
	}
}
}
	