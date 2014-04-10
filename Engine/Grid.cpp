#include "Grid.h"

using namespace std;

namespace karo {
	void Grid::Traverse(unsigned x, unsigned y, IGridTraveller* traveller) {
		traveller->ReceiveTile(GetTileAt(x, y));
	}

	int Grid::GetTileIndex(unsigned x, unsigned y) const {
		return x + y * _size->GetWidth();
	}

	void Grid::Init(unsigned width, unsigned height) {
		_tilesLength = (unsigned) (width * height);
		_size = new Size(width, height);
		_tiles = new vector<Tile*>();
		for (unsigned y = 0; y < height; y++) {
			for (unsigned x = 0; x < width; x++) {
				_tiles->push_back(new Tile(new Vector2D(x, y)));
			}
		}
		// bind tiles to each other
		for (unsigned y = 0; y < height; y++) {
			for (unsigned x = 0; x < width; x++) {

				try {
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
				} catch (const out_of_range& oor) {

					// the default exception is just crap
					cout << "binding failed at point:"
							<< " x:" << StrConverter::IntToString(x)
							<< " y:" << StrConverter::IntToString(y)
							<< endl << "message: "
							<< oor.what()
							<< endl;
				}

			}
		}
	}

	Grid::Grid() {
		Init(C_default_w, C_default_h);
	}

	Grid::Grid(unsigned width, unsigned height) {
		Init(width, height);
	}

	Grid::~Grid() {
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

	void sizeMessage(unsigned x, unsigned y) {
		// I used to just log this, but usualy when this happens the aplication crashed anyways,
		// so this will do fine
		throw "Unable to find tile at "
		"x: " + StrConverter::IntToString(x)
				+ "y: " + StrConverter::IntToString(y);
	};


	Tile* Grid::GetTileAt(Vector2D& p) const {
		unsigned desiredIndex = GetTileIndex(p.X(), p.Y());
		if (desiredIndex < 0) {
			sizeMessage(x, y);
		}
		if (desiredIndex > _tilesLength) {
			sizeMessage(x, y);
		}
		return _tiles->at(desiredIndex);
	}

	void Grid::TraverseRow(unsigned y, IGridTraveller* traveller) {
		for (unsigned x = 0; x < _size->GetWidth(); x++) {
			Traverse(x, y, traveller);
		}
	}

	void Grid::TraverseCollumn(unsigned x, IGridTraveller* traveller) {
		for (unsigned y = 0; y < _size->GetHeight(); y++) {
			Traverse(x, y, traveller);
		}
	}

	void Grid::TraverseTiles(IGridTraveller* traveller) {
		for (unsigned x = 0; x < _size->GetWidth(); x++) {
			TraverseCollumn(x, traveller);
		}
	}

	Size* Grid::GetSize() const {
		return _size;
	}

	vector<Tile*> Grid::GetSurroundingTiles(vector<Tile*> tiles) const {
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

	vector<Tile*> Grid::GetTilesInRectangle(Vector2D topLeft, Vector2D bottomRight) const {
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
}
