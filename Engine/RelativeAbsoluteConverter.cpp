#include "RelativeAbsoluteConverter.h"
namespace engine{

	RelativeAbsoluteConverter::RelativeAbsoluteConverter(){
		Init(NULL, Vector2D());
	}
	RelativeAbsoluteConverter::RelativeAbsoluteConverter(Grid<int>* parsable){
		Init(parsable, Vector2D());
	}

	RelativeAbsoluteConverter::RelativeAbsoluteConverter(Grid<int>* parseable, Vector2D tl){
		Init(parseable, tl);
	}
	void RelativeAbsoluteConverter::Init(Grid<int>* parsable, Vector2D tl){
		if(parsable == NULL){
			return;
		}
		_topLeft = tl;
		_rowTileCount = vector<int>();
		_colTileCount = vector<int>();
		for(unsigned i = 0; i < parsable->GetSize()->GetWidth(); i++){
			_rowTileCount.push_back(int(0));
		}
		for(unsigned i = 0; i < parsable->GetSize()->GetHeight(); i++){
			_colTileCount.push_back(int(0));
		}
		parsable->TraverseCells(
			[this](Cell<int>* tile) -> void {
				if(tile->GetData() & HasTile){
					this->_rowTileCount.at((int)tile->GetPosition().X())+=1;
					this->_rowTileCount.at((int)tile->GetPosition().Y())+=1;
				}
			}
		);
	}
	Vector2D RelativeAbsoluteConverter::ToRelative(const Vector2D& input)const{
		return WrapArround(input - _topLeft);
	}
	Vector2D RelativeAbsoluteConverter::ToAbsolute(const Vector2D& input)const{
		return WrapArround(input + _topLeft);
	}

	Vector2D& RelativeAbsoluteConverter::WrapArround(Vector2D& input)const{
		if(input.X() < 0){
			input.X(input.X() + GridWidth());
		}
		if(input.Y() < 0){
			input.Y(input.Y() + GridHeight());
		}
		if(input.X() >= GridWidth()){
			input.X(0);
		}
		if(input.Y() >= GridHeight()){
			input.Y(0);
		}
		return input;
	}
	// allows the converter to be kept up to date with board
	void RelativeAbsoluteConverter::MoveTile(const Vector2D& from, const Vector2D& to){
		// update tilecounts
		_colTileCount.at((int)from.X())--;
		_rowTileCount.at((int)from.Y())--;
		_colTileCount.at((int)to.X())++;
		_rowTileCount.at((int)to.Y())++;

		// handle the topleft changes
		// the down right part
		// if the topleft collumn has no tiles in it the topleft shifted right
		if(_colTileCount.at((int)_topLeft.X()) == 0){
			_topLeft.X(_topLeft.X() -1);
		}
		// if the top left row has no tiles in it the topleft shifted down
		if(_rowTileCount.at((int)_topLeft.Y()) == 0){
			_topLeft.Y(_topLeft.Y() -1);
		}

		// the up left part
		Vector2D difference = to - _topLeft;
		if(to.Y() == _topLeft.Y()){
			if(to.X() < _topLeft.X()){
				_topLeft.X(to.X());
			}
			// wrap arround case not absolute because these comparisons are only for up and left
			if(difference.X() == 19){
				_topLeft.X(to.X());
			}
		}
		if(to.Y() < _topLeft.Y()){
			_topLeft = to;
		}
		// wrap arround case
		if(difference.Y() == 19){
			_topLeft = to;
		}
	}


	int RelativeAbsoluteConverter::GridWidth()const{
		return _colTileCount.size();
	}
	int RelativeAbsoluteConverter::GridHeight()const{
		return _rowTileCount.size();
	}
}