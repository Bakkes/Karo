#include "RelativeAbsoluteConverter.h"
namespace engine{

	RelativeAbsoluteConverter::RelativeAbsoluteConverter(Grid<int>* parsable){
		Vector2D _topLeft = Vector2D();
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
		_rowTileCount.at((int)from.X());
	}


	int RelativeAbsoluteConverter::GridWidth()const{
		return _colTileCount.size();
	}
	int RelativeAbsoluteConverter::GridHeight()const{
		return _rowTileCount.size();
	}
}