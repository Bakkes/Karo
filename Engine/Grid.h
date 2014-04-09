#pragma once

#include <vector>
#include "Tile.h"
#include "Size.h"
#include "Vector2D.h"
#include "IGridTraveller.h"
#include <iostream>
#include "StrConverter.h"
#include <stdexcept>
#include "Exceptions.h"
#include <algorithm>
#include "GridGraphicTranslator.h"

using namespace std;

namespace karo {
	// A class for easaly handaling a grid as a one dimensional array, with O(1) accessing speed for positions,
	// and O(N), for accesing any set of elements.
	// it also handy for traversel of indivdual rows/columns or all tiles trough passing an object
	// which inherits from the interface like IGridTraveller
	class Grid {
	public:
		// default constructor will use the C_default_size for initiliztion
		Grid();
		// initialize the grid to the specified size
		Grid(unsigned width, unsigned height);
		~Grid();

		// shorthand for getTileAt(int x, int y)
		Tile* GetTileAt(Vector2D& p) const;

		// The given function pointer will receive all the tiles and coordinates in the specified row
		void TraverseRow(unsigned y, IGridTraveller* travellar);
		// The given function pointer will receive all the tiles and coordinates in the specified collumn
		void TraverseCollumn(unsigned x, IGridTraveller* travellar);
		// The given function pointer will receive all the tiles in the grid and the cordiantes of them.
		void TraverseTiles(IGridTraveller* travellar);
		Size* GetSize() const;
		vector<Tile*> GetSurroundingTiles(vector<Tile*>) const;
		vector<Tile*> GetTilesInRectangle(Vector2D topLeft, Vector2D bottomRight) const;

	private:
		vector<Tile*>* _tiles;
		unsigned _tilesLength;
		static const unsigned C_default_h = 20;
		static const unsigned C_default_w = 20;
		// size of the grid
		Size* _size;
		// final step in the traversal proces, here the cordinates are known and only the
		// functionpointer has to be called
		void Traverse(unsigned x, unsigned y, IGridTraveller* travellar);
		
		// comman code for both contructors
		void Init(unsigned width, unsigned height);
		// this function prevents the same calculation showing up in several places
		int GetTileIndex(unsigned x, unsigned y) const;
	};
}
