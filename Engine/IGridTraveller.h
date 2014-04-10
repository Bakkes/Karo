#pragma once
namespace karo {
	template<typename T>
	class Tile;
	// 'pure virtual' or an interface, classes that extend this class will be able to traverse the
	// grid.
	// a class implementing this interface can be given to the traverse* methods of grid and receive
	// the tiles in the row column or grid.
	template<typename T>
	class IGridTraveller{
	public:
		virtual ~IGridTraveller() {}
		virtual void ReceiveTile(Tile<T>* tile) = 0;
	};
}
