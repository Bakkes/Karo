using Microsoft.Xna.Framework;

namespace XNAFrontend.Services
{
	interface ICamera
	{
		Vector3 Position { get; }
		Matrix Projection { get; }
		Matrix View { get; }
	}
}
