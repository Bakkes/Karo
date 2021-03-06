#pragma once

#include <vector>
#include "Cell.h"
#include "Size.h"
#include "Vector2D.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>
using namespace std;

namespace engine {
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
		Cell<T>* GetCellAt(const Vector2D& position) const{
			unsigned desiredIndex = GetCellIndex((unsigned)position.X(),(unsigned) position.Y());
			if (desiredIndex < 0) {
				throw "trying to get a tile at a wrong position";
			}
			if (desiredIndex >= _tilesLength) {
				throw "trying to get a tile at a wrong position";
			}
			return _tiles->at(desiredIndex);
		}

		// The given function pointer will receive all the tiles and coordinates in the specified row
		void TraverseRow(unsigned y, function< void(Cell<T>*) >& lambda){
			for (unsigned x = 0; x < _size->GetWidth(); x++) {
				Traverse(x, y, lambda);
			}
		}
		// The given function pointer will receive all the tiles and coordinates in the specified collumn
		void TraverseCollumn(unsigned x, function< void(Cell<T>*) >& lambda){
			for (unsigned y = 0; y < _size->GetHeight(); y++) {
				Traverse(x, y, lambda);
			}
		}
		// The given function pointer will receive all the tiles in the grid and the cordiantes of them.
		void TraverseCells(function< void(Cell<T>*) > lambda){
			for (unsigned y = 0; y < _size->GetHeight(); y++) {
				TraverseRow(y, lambda);
			}
		}
		Size* GetSize() const{
			return _size;
		}

		void BindCellsToEachother(bool wrapArround = false){
			unsigned height = _size->GetHeight();
			unsigned width = _size->GetWidth();
			// bind tiles to each other
			for (unsigned y = 0; y < height; y++) {
				for (unsigned x = 0; x < width; x++) {

					if (y < height - 1) {
						_tiles->at(GetCellIndex(x, y))->SetBottom(
							_tiles->at(
								GetCellIndex(x, y + 1)
							)
						);
					}else if(wrapArround){
						_tiles->at(GetCellIndex(x,y))->SetBottom(
							_tiles->at(
								GetCellIndex(x,0)
							)
						);
					}
					if (y != 0) {
						_tiles->at(GetCellIndex(x, y))->SetTop(
							_tiles->at(
								GetCellIndex(x, y - 1)
							)
						);
					}else if(wrapArround){
						_tiles->at(GetCellIndex(x, y))->SetTop(
							_tiles->at(
								GetCellIndex(x, height - 1)
							)
						);
					}

					if (x < width - 1) {
						_tiles->at(GetCellIndex(x, y))->SetRight(
							_tiles->at(
								GetCellIndex(x + 1, y)
							)
						);
					}else if(wrapArround){
						_tiles->at(GetCellIndex(x, y))->SetRight(
							_tiles->at(
								GetCellIndex(0, y)
							)
						);

					}

					if (x != 0) {
						_tiles->at(GetCellIndex(x, y))->SetLeft(
							_tiles->at(
								GetCellIndex(x - 1, y)
							)
						);
					}else if(wrapArround){
						_tiles->at(GetCellIndex(x, y))->SetLeft(
							_tiles->at(
								GetCellIndex(width -1, y)
							)
						);
					}
				}
			}

		}

	private:
		vector<Cell<T>*>* _tiles;
		unsigned _tilesLength;
		static const unsigned C_default_w = 20;
		static const unsigned C_default_h = 20;
		// size of the grid
		Size* _size;
		// final step in the traversal proces, here the cordinates are known and only the
		// functionpointer has to be called
		void Traverse(unsigned x, unsigned y,function< void(Cell<T>*) > lambda){
			lambda(GetCellAt(Vector2D(x, y)));
		}
		
		// commen code for both contructors
		void Init(unsigned width, unsigned height){
			_tilesLength = (unsigned) (width * height);
			_size = new Size(width, height);
			_tiles = new vector<Cell<T>*>();
			for (unsigned y = 0; y < height; y++) {
				for (unsigned x = 0; x < width; x++) {
					_tiles->push_back(new Cell<T>(Vector2D(x, y)));
				}
			}
			BindCellsToEachother();
		}
		// this function prevents the same calculation showing up in several places
		int GetCellIndex(const unsigned x, const unsigned y) const {
			return x + y * _size->GetWidth();
		}
	};
}
