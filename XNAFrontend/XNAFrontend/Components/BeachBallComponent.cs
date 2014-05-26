using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace XNAFrontend.Components
{
	public class BeachBallComponent : ACommonComponent
	{
		private Vector3 _gravity;
		private readonly Vector3 _maxVelocity;

		private Model _beachBall;
		private Vector3 _position;
		private Vector3 _velocity;
		private float _rotation;

		private Vector3 _offset;
		private Vector3 _cameraPosition;
		private Matrix _view;
		private Matrix _projection;

		public BeachBallComponent(KaroGame game)
			: base(game)
		{
			_gravity = new Vector3(0f, 0.08f, 0f);
			_position = Vector3.Zero;
			_maxVelocity = new Vector3(0f, 1.3f, 0f);
			_velocity = _maxVelocity;

			float aspectRatio = Game.GraphicsDevice.Viewport.AspectRatio;
			_cameraPosition = new Vector3(20f, 0f, 0f);
			_view = Matrix.CreateLookAt(_cameraPosition, _position, Vector3.Up);
			_projection = Matrix.CreatePerspectiveFieldOfView(
				MathHelper.ToRadians(45f),
				aspectRatio, 0.1f, 25f
			);

			_offset = new Vector3(0f, -5f, 0f);
		}

		protected override void LoadContent()
		{
			_beachBall = Game.Content.Load<Model>("beachball");
			base.LoadContent();
		}

		public override void Update(GameTime gameTime)
		{
			_velocity -= _gravity;
			_position += _velocity;
			if (_position.Y < 0f)
			{
				_velocity = _maxVelocity;
			}
			_rotation += 0.15f;
			base.Update(gameTime);
		}

		public override void Draw(GameTime gameTime)
		{
			base.Draw(gameTime);

			RasterizerState rs = new RasterizerState();
			rs.DepthBias = -10f;
			RasterizerState rsold = Game.GraphicsDevice.RasterizerState;
			Game.GraphicsDevice.RasterizerState = rs;
			foreach (ModelMesh mesh in _beachBall.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.EnableDefaultLighting();
					effect.View = _view;
					effect.Projection = _projection;
					effect.World = Matrix.CreateRotationZ(1.5f) *
						Matrix.CreateRotationX(_rotation) *
						Matrix.CreateTranslation(_position) *
						Matrix.CreateTranslation(_offset);
				}
				mesh.Draw();
			}
			Game.GraphicsDevice.RasterizerState = rsold;
		}
	}
}
