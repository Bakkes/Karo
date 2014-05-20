using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace XNAFrontend.Services
{
	class Camera : ICamera
	{
		private Vector3 _position;

		/// <summary>
		/// The position of the camera in world space
		/// </summary>
		public Vector3 Position
		{
			get
			{
				return _position;
			}
			set
			{
				_position = value;
				View = Matrix.CreateLookAt(value, new Vector3(value.X, 0, 0), Vector3.Up);
			}
		}
		/// <summary>
		/// The projection matrix which transforms our 3D world into 2D space
		/// </summary>
		public Matrix Projection { get; set; }
		/// <summary>
		/// The matrix which defines how we look at the world
		/// </summary>
		public Matrix View { get; set; }

        public Camera(Viewport viewport)
        {
			Position = new Vector3(0, 5, 5);
			Projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.PiOver4, viewport.AspectRatio, 0.001f, 10000);
        }
	}
}
