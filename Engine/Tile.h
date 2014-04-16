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
	class ENGINE_API Tile{
	public:
		// set a tile to the point
		Tile(Vector2D* p){
			Init(p);
		}

		~Tile(){
			if(_position){
				delete _position;
			}
			if(_tiledata){
				delete _tiledata;
			}
			_top = NULL;
			_left = NULL;
			_right = NULL;
			_bottom = NULL;
			_position = NULL;
			_tiledata = NULL;
		}

		void SetBottom(Tile<T>* bottom){
			this->_bottom = bottom;
		}
		Tile<T>* GetBottom() const{
			return _bottom;
		}
		void SetRight(Tile<T>* right){
			this->_right = right;
		}
		Tile<T>* GetRight() const{
			return _right;
		}
		void SetLeft(Tile<T>* left){
			this->_left = left;
		}
		Tile<T>* GetLeft() const{
			return _left;
		}
		void SetTop(Tile<T>* top){
			this->_top = top;
		}
		Tile<T>* GetTop() const{
			return _top;
		}
		Vector2D* GetPosition() const{
			return _position;
		}
		void SetData(T* data){
			_tiledata = data;
		}
		T* GetData() const{
			return _tiledata;
		}
		vector<Tile<T>*> GetSurroundingTiles() const{
			vector<Tile<T>*> tiles;
			tiles.push_back(this->GetLeft());
			tiles.push_back(this->GetTop());
			tiles.push_back(this->GetRight());
			tiles.push_back(this->GetBottom());
			return tiles;
		}
	private:
		void Init(Vector2D* p){
			_position = p;
			_tiledata = NULL;
			_bottom = NULL;
			_top = NULL;
			_left = NULL;
			_right = NULL;
		}
		T* _tiledata;
		Vector2D* _position;
		Tile<T>* _top;
		Tile<T>* _left;
		Tile<T>* _right;
		Tile<T>* _bottom;
	};
	inline bool ENGINE_API operator==(const Tile<int>& l, const Tile<int>& r){
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
	inline bool ENGINE_API operator!=(const Tile<int>& l, const Tile<int>& r){return !operator==(l,r);}
}
