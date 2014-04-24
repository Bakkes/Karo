#pragma once

#include <vector>
#include <cstdlib>
#include "Vector2D.h"

using namespace std;
namespace engine {
	// a container class for stuff in the grid.
	// this class is for easy navigating the grid, when you get a tile you now
	// its neighbours
	template<typename T>
	class ENGINE_API Cell{
	public:
		// Copy constructor
		Cell(const Cell<T> &src) {
			_position = Vector2D(src._position);
			_left = src._left;
			_right = src._right;
			_top = src._top;
			_bottom = src._bottom;
			_tiledata = src._tiledata;
		}

		// set a tile to the point
		Cell(Vector2D& p){
			Init(p);
		}

		~Cell(){
			delete _tiledata;
			_top = NULL;
			_left = NULL;
			_right = NULL;
			_bottom = NULL;
			_position = NULL;
			_tiledata = NULL;
		}

		void SetBottom(Cell<T>* bottom){
			this->_bottom = bottom;
		}
		Cell<T>* GetBottom() const{
			return _bottom;
		}
		void SetRight(Cell<T>* right){
			this->_right = right;
		}
		Cell<T>* GetRight() const{
			return _right;
		}
		void SetLeft(Cell<T>* left){
			this->_left = left;
		}
		Cell<T>* GetLeft() const{
			return _left;
		}
		void SetTop(Cell<T>* top){
			this->_top = top;
		}
		Cell<T>* GetTop() const{
			return _top;
		}
		const Vector2D& GetPosition() const {
			return _position;
		}
		void SetData(T* data){
			_tiledata = data;
		}
		T* GetData() const{
			return _tiledata;
		}
		vector<Cell<T>*> GetSurroundingCells() const{
			vector<Cell<T>*> tiles;
			tiles.push_back(this->GetLeft());
			tiles.push_back(this->GetTop());
			tiles.push_back(this->GetRight());
			tiles.push_back(this->GetBottom());
			return tiles;
		}
	private:
		void Init(Vector2D& p){
			_position = p;
			_tiledata = NULL;
			_bottom = NULL;
			_top = NULL;
			_left = NULL;
			_right = NULL;
		}
		T* _tiledata;
		Vector2D _position;
		Cell<T>* _top;
		Cell<T>* _left;
		Cell<T>* _right;
		Cell<T>* _bottom;
	};
	inline bool ENGINE_API operator==(const Cell<int>& l, const Cell<int>& r){
		if(l.GetPosition() != r.GetPosition()){
			return false;
		}
		// don't compare the actual states of the neighbours,
		// because it will recusrivle call their == operators as well
		// just checking their identity trough pointers is way faster
		// and sort of reliable (not for pointer pointers, but this may be
		// handled by the type system)
		if(l.GetTop() != r.GetTop()){
			return false;
		}
		if(l.GetLeft() != r.GetLeft()){
			return false;
		}
		if(l.GetBottom() != r.GetBottom()){
			return false;
		}
		if(l.GetRight() != r.GetRight()){
			return false;
		}
		return true;
	}
	inline bool ENGINE_API operator!=(const Cell<int>& l, const Cell<int>& r){return !operator==(l,r);}
}
