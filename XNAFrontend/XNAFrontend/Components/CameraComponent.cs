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
	public class CameraComponent : ACommonComponent
	{
		private const float MaxPitch = -MathHelper.TwoPi / 40;
		private const float MinPitch = -MathHelper.PiOver2 + 0.01f;

		private ICamera Camera
		{
			get
			{
				return (ICamera)Game.Services.GetService(typeof(ICamera));
			}
		}

		private Vector3 _targetPosition;
		private float _zoom;

		private float _yaw;
		private float _pitch;

		private float _nearPlane;
		private float _farPlane;

		private float _speed;

		public CameraComponent(KaroGame game, Vector3 targetPosition)
			: base(game)
		{
			Viewport viewport = game.GraphicsDevice.Viewport;
			_targetPosition = targetPosition;

			_yaw = -MathHelper.ToRadians(45);
			_pitch = -MathHelper.ToRadians(45);
			_zoom = 8f;


			_nearPlane = 1f;
			_farPlane = 400f;

			_speed = 0.05f;
		}

		/// <summary>
		/// Allows the game component to perform any initialization it needs to before starting
		/// to run.  This is where it can query for any required services and load content.
		/// </summary>
		public override void Initialize()
		{
			RecreateViewMatrix();
			RecreateProjectionMatrix();

			base.Initialize();
		}

		/// <summary>
		/// Allows the game component to update itself.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		public override void Update(GameTime gameTime)
		{
			KeyboardState state = Keyboard.GetState();
			if (state.IsKeyDown(Keys.Left))
			{
				_yaw += _speed;
			}
			if (state.IsKeyDown(Keys.Right))
			{
				_yaw -= _speed;
			}
			if (state.IsKeyDown(Keys.Up))
			{
				_pitch += _speed;
			}
			if (state.IsKeyDown(Keys.Down))
			{
				_pitch -= _speed;
			}

			_pitch = MathHelper.Clamp(_pitch, MinPitch, MaxPitch);

			RecreateViewMatrix();
			base.Update(gameTime);
		}

		private void RecreateViewMatrix()
		{
			Vector3 relativePosition = Vector3.Transform(Vector3.Backward, Matrix.CreateFromYawPitchRoll(_yaw, _pitch, 0));
			Vector3 position = relativePosition * _zoom + _targetPosition;
			Camera.View = Matrix.CreateLookAt(position, _targetPosition, Vector3.Up);
		}

		private void RecreateProjectionMatrix()
		{
			float aspectRatio = Game.GraphicsDevice.Viewport.AspectRatio;
			Camera.Projection = Matrix.CreatePerspectiveFieldOfView(
				MathHelper.PiOver4, aspectRatio, _nearPlane, _farPlane
			);
		}
	}
}
