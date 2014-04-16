using System.Drawing;

namespace _2DFrontend.State
{
	/// <summary>
	/// Interface for karo game states. Takes a tile coordinate and
	/// performs an action depending on the coordinate and state.
	/// Implementations of this interface should be a singleton.
	/// </summary>
	interface IKaroState
	{
		IKaroState Instance { get; set; }
		void Update(KaroGameManager manager, Point click);
	}
}
