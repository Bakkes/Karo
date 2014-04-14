#pragma once

#include <vector>
#include "Size.h"
#include "Vector2D.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

namespace engine {
	// A class for easaly handaling a grid as a one dimensional array, with O(1) accessing speed for positions
	template<typename T>
	class Grid {
	public:
		// default constructor will use the C_default_size for initiliztion
		Grid() {
			Init(C_default_w, C_default_h);
		}
		// initialize the grid to the specified size
		Grid(unsigned width, unsigned height) {
			Init(width, height);
		}
		~Grid() {
			for (auto it = _tiles->begin(); it != _tiles->end(); ++it) {
				delete (*it);
			}
			if(_tiles) {
				delete _tiles;
			}
			if(_size) {
				delete _size;
			}
			_tiles = NULL;
			_size = NULL;
		}

		// get tile at position
		T& GetTileAt(Vector2D& position) const {
			unsigned desiredIndex = GetTileIndex(p.X(), p.Y());
			if (desiredIndex < 0) {
				sizeMessage(x, y);
			}
			if (desiredIndex > _tilesLength) {
				sizeMessage(x, y);
			}
			return *_tiles->at(desiredIndex);
		}
		Size* GetSize() const {
			return _size;
		}
	private:
		vector<T*>* _tiles;
		unsigned _tilesLength;
		static const unsigned C_default_w = 20;
		static const unsigned C_default_h = 20;
		// size of the grid
		Size* _size;
		
		// common code for both contructors
		void Init(unsigned width, unsigned height) {
			_tilesLength = (unsigned) (width * height);
			_size = new Size(width, height);
			_tiles = new vector<T*>();
			for (unsigned y = 0; y < height; y++) {
				for (unsigned x = 0; x < width; x++) {
					_tiles->push_back(NULL);
				}
			}
		}
		// this function prevents the same calculation showing up in several places
		int GetTileIndex(const unsigned x, const unsigned y) const {
			return x + y * _size->GetWidth();
		}
	};
}
