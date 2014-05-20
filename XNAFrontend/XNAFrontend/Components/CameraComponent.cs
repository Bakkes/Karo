using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using XNAFrontend.Services;

namespace XNAFrontend.Components
{
	/// <summary>
	/// This is a game component that implements IUpdateable.
	/// </summary>
	public class CameraComponent : ACommonComponent, ICamera
	{
		private const float MaxPitch = -MathHelper.TwoPi / 40;
		private const float MinPitch = -MathHelper.PiOver2 + 0.01f;

		private const float MinZoom = 5f;
		private const float MaxZoom = 20f;

		private const float MoveSpeed = 0.05f;
		private const float ZoomSpeed = 0.15f;

		private Matrix _projection;
		private Matrix _view;

		private Vector3 _relativePosition;
		private Vector3 _targetPosition;
		private float _zoom;

		private float _yaw;
		private float _pitch;

		private float _nearPlane;
		private float _farPlane;


		public Vector3 Position
		{
			get { return _relativePosition * _zoom + _targetPosition; }
		}

		public Matrix Projection
		{
			get { return _projection; }
		}

		public Matrix View
		{
			get { return _view; }
		}

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
				_yaw += MoveSpeed;
			}
			if (state.IsKeyDown(Keys.Right))
			{
				_yaw -= MoveSpeed;
			}
			if (state.IsKeyDown(Keys.Up))
			{
				_pitch -= MoveSpeed;
			}
			if (state.IsKeyDown(Keys.Down))
			{
				_pitch += MoveSpeed;
			}

			if (state.IsKeyDown(Keys.Add))
			{
				_zoom -= ZoomSpeed;
			}
			if (state.IsKeyDown(Keys.Subtract))
			{
				_zoom += ZoomSpeed;
			}

			_pitch = MathHelper.Clamp(_pitch, MinPitch, MaxPitch);
			_zoom = MathHelper.Clamp(_zoom, MinZoom, MaxZoom);

			RecreateViewMatrix();
			RecreateProjectionMatrix();
			base.Update(gameTime);
		}

		private void RecreateViewMatrix()
		{
			_relativePosition = Vector3.Transform(Vector3.Backward, Matrix.CreateFromYawPitchRoll(_yaw, _pitch, 0));
			_view = Matrix.CreateLookAt(Position, _targetPosition, Vector3.Up);
		}

		private void RecreateProjectionMatrix()
		{
			float aspectRatio = Game.GraphicsDevice.Viewport.AspectRatio;
			_projection = Matrix.CreatePerspectiveFieldOfView(
				MathHelper.PiOver4, aspectRatio, _nearPlane, _farPlane
			);
		}
	}
}
