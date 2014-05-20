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
		/// <summary>
		/// The position of the camera in world space
		/// </summary>
		private Vector3 _position;
		/// <summary>
		/// The projection matrix which transforms our 3D world into 2D space
		/// </summary>
		private Matrix _projection;
		/// <summary>
		/// The matrix which defines how we look at the world
		/// </summary>
		private Matrix _view;

		public Vector3 Position
		{
			get
			{
				return _position;
			}
		}

		public Matrix Projection
		{
			get
			{
				return _projection;
			}
		}

		public Matrix View
		{
			get
			{
				return _view;
			}
		}

        public Camera(Viewport viewport)
        {
			_position = new Vector3(2.75f, 5, 5);
			_projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.PiOver4, viewport.AspectRatio, 0.1f, 10000);
			_view = Matrix.CreateLookAt(_position, new Vector3(2.75f, 0, 0), Vector3.Up);
        }
	}
}
