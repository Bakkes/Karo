#pragma once

#include <vector>
#include <cstdlib>
#include "Vector2D.h"
#include "IPaintable.h"
#include "ITileData.h"

namespace karo {
	// a container class for stuff in the grid.
	// this class is for easy navigating the grid, when you get a tile you now
	// its neighbours
	class Tile : IPaintable{
	public:
		// set a tile to the point
		Tile(Vector2D* p);
		// set a tile to x,y
		Tile(int x, int y);

		~Tile();

		void SetBottom(Tile* bottom);
		Tile* GetBottom() const;
		void SetRight(Tile* right);
		Tile* GetRight() const;
		void SetLeft(Tile* left);
		Tile* GetLeft() const;
		void SetTop(Tile* top);
		Tile* GetTop() const;
		Vector2D* GetPosition() const;
		void Paint(Graphics* g);
		void SetData(ITileData*);
		ITileData* GetData() const;
		vector<Tile*> GetSurroundingTiles() const;
	private:
		void Init(Vector2D* p);
		ITileData* _tiledata;
		Vector2D* _position;
		Tile* _top;
		Tile* _left;
		Tile* _right;
		Tile* _bottom;
		bool _hasData;
	};
	inline bool operator==(const Tile& l, const Tile& r){
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
	// forward operations to the once that actualy do somthing
	inline bool operator!=(const Tile& l, const Tile& r){return !operator==(l,r);}
}
