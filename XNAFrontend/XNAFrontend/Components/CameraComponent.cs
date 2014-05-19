using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using XNAFrontend.Services;


namespace XNAFrontend.Components
{
    /// <summary>
    /// This is a game component that implements IUpdateable.
    /// </summary>
    public class CameraComponent : ACommonComponent, ICamera
    {
		private Vector3 _position;
		private Matrix _projection;
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

        public CameraComponent(KaroGame game) : base(game)
        {
			Viewport viewport = game.GraphicsDevice.Viewport;

			_position = new Vector3(2.75f, 5, 5);
			_projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.PiOver4, viewport.AspectRatio, 0.1f, 10000);
			_view = Matrix.CreateLookAt(_position, new Vector3(2.75f, 0, 0), Vector3.Up);
        }

        /// <summary>
        /// Allows the game component to perform any initialization it needs to before starting
        /// to run.  This is where it can query for any required services and load content.
        /// </summary>
        public override void Initialize()
        {
            base.Initialize();
        }

        /// <summary>
        /// Allows the game component to update itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }

	}
}
