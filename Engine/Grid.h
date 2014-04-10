#pragma once

#include <vector>
#include "Tile.h"
#include "Size.h"
#include "Vector2D.h"
#include "IGridTraveller.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

namespace karo {
	// A class for easaly handaling a grid as a one dimensional array, with O(1) accessing speed for positions,
	// and O(N), for accesing any set of elements.
	// it also handy for traversel of indivdual rows/columns or all tiles trough passing an object
	// which inherits from the interface like IGridTraveller
	template<typename T>
	class Grid {
	public:
		// default constructor will use the C_default_size for initiliztion
		Grid(){
			Init(C_default_w, C_default_h);
		}
		// initialize the grid to the specified size
		Grid(unsigned width, unsigned height){
			Init(width, height);
		}
		~Grid(){
			for (auto it = _tiles->begin(); it != _tiles->end(); ++it) {
				delete (*it);
			}
			if(_tiles){
				delete _tiles;
			}
			if(_size){
				delete _size;
			}
			_tiles = NULL;
			_size = NULL;
		}

		// get tile at position
		Tile<T>* GetTileAt(Vector2D& position) const{
			unsigned desiredIndex = GetTileIndex(p.X(), p.Y());
			if (desiredIndex < 0) {
				sizeMessage(x, y);
			}
			if (desiredIndex > _tilesLength) {
				sizeMessage(x, y);
			}
			return _tiles->at(desiredIndex);
		}

		// The given function pointer will receive all the tiles and coordinates in the specified row
		void TraverseRow(unsigned y, IGridTraveller<T>* travellar){
			for (unsigned x = 0; x < _size->GetWidth(); x++) {
				Traverse(x, y, traveller);
			}
		}
		// The given function pointer will receive all the tiles and coordinates in the specified collumn
		void TraverseCollumn(unsigned x, IGridTraveller<T>* travellar){
			for (unsigned y = 0; y < _size->GetHeight(); y++) {
				Traverse(x, y, traveller);
			}
		}
		// The given function pointer will receive all the tiles in the grid and the cordiantes of them.
		void TraverseTiles(IGridTraveller<T>* travellar){
			for (unsigned x = 0; x < _size->GetWidth(); x++) {
				TraverseCollumn(x, traveller);
			}
		}
		Size* GetSize() const{
			return _size;
		}
		vector<Tile<T>*> GetSurroundingTiles(vector<Tile<T>*>) const{
			vector<Tile*> allTiles;
			allTiles.reserve(tiles.size() * 4);
			for(unsigned i = 0; i < tiles.size(); i++) {
				Tile* t = tiles.at(i);
				std::vector<Tile*> surrounding = t->GetSurroundingTiles();
				allTiles.insert(allTiles.end(), surrounding.begin(), surrounding.end());
			}
			std::sort(allTiles.begin(), allTiles.end());
			std::sort(tiles.begin(), tiles.end());
			std::vector<Tile*> difference;
			std::set_difference(allTiles.begin(), allTiles.end(), tiles.begin(), tiles.end(), std::back_inserter(difference));
			return difference;
		}
		vector<Tile<T>*> GetTilesInRectangle(Vector2D topLeft, Vector2D bottomRight) const{
			GridGraphicTranslator translator = GridGraphicTranslator();
			vector<Tile*> includedTiles;

			Vector2D p = translator.ToFrom(topLeft);
			Tile* topLeftTile = GetTileAt(p);
			Tile* topRightTile = GetTileAt(translator.ToFrom(bottomRight));

			for(double i = topLeftTile->GetPosition()->X(); i <= topRightTile->GetPosition()->X(); i++) {
				for(double j = topLeftTile->GetPosition()->Y(); j <= topRightTile->GetPosition()->Y(); j++) {
					includedTiles.push_back(GetTileAt((int)i, (int)j));
				}
			}
			return includedTiles;
		}

	private:
		vector<Tile<T>*>* _tiles;
		unsigned _tilesLength;
		static const unsigned C_default_w = 20;
		static const unsigned C_default_h = 20;
		// size of the grid
		Size* _size;
		// final step in the traversal proces, here the cordinates are known and only the
		// functionpointer has to be called
		void Traverse(unsigned x, unsigned y, IGridTraveller<T>* travellar){
			traveller->ReceiveTile(GetTileAt(x, y));
		}
		
		// commen code for both contructors
		void Init(unsigned width, unsigned height){
			_tilesLength = (unsigned) (width * height);
			_size = new Size(width, height);
			_tiles = new vector<Tile<T>*>();
			for (unsigned y = 0; y < height; y++) {
				for (unsigned x = 0; x < width; x++) {
					_tiles->push_back(new Tile<T>(new Vector2D(x, y)));
				}
			}
			// bind tiles to each other
			for (unsigned y = 0; y < height; y++) {
				for (unsigned x = 0; x < width; x++) {

					if (y < height - 2) {
						_tiles->at(GetTileIndex(x, y))->SetTop(
							_tiles->at(
								GetTileIndex(x, y + 1)
							)
						);
					}

					if (y != 0) {
						_tiles->at(GetTileIndex(x, y))->SetBottom(
							_tiles->at(
								GetTileIndex(x, y - 1)
							)
						);
					}

					if (x < width - 2) {
						_tiles->at(GetTileIndex(x, y))->SetRight(
							_tiles->at(
								GetTileIndex(x + 1, y)
							)
						);
					}

					if (x != 0) {
						_tiles->at(GetTileIndex(x, y))->SetLeft(
							_tiles->at(
								GetTileIndex(x - 1, y)
							)
						);
					}
				}
			}
		}
		// this function prevents the same calculation showing up in several places
		int GetTileIndex(const unsigned x, const unsigned y) const{
			return x + y * _size->GetWidth();
		}
	};
}
