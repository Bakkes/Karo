using Microsoft.Xna.Framework;

namespace XNAFrontend.Services
{
	interface ICamera
	{
		/// <summary>
		/// The projection matrix which transforms our 3D world into 2D space
		/// </summary>
		Matrix Projection { get; set; }
		/// <summary>
		/// The matrix which defines how we look at the world
		/// </summary>
		Matrix View { get; set; }
	}
}
