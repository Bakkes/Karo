using System.Drawing;

namespace KaroManager.State
{
	/// <summary>
	/// Interface for karo game states. Takes a tile coordinate and
	/// performs an action depending on the coordinate and state.
	/// Implementations of this interface should be a singleton.
	/// </summary>
	public interface IKaroState
	{
		void Enter(KaroGameManager manager);
		void Update(KaroGameManager manager, Point click);
		void Exit(KaroGameManager manager);
	}
}
