using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace XNAFrontend.Components
{
	/// <summary>
	/// 3D board representation of the karo board game.
	/// </summary>
	internal class Board : DrawableGameComponent
	{
		private Vector3 Position = Vector3.One;
		private float Zoom = 2500;
		private float RotationY = 0.0f;
		private float RotationX = 0.0f;
		private Matrix gameWorldRotation;
		private Model _tileModel;

		private KaroGame KaroGame { get { return (KaroGame)this.Game; } }

		public Board(KaroGame game)
			: base(game)
		{
			LoadContent();
		}

		protected override void LoadContent()
		{
			base.LoadContent();
			_tileModel = Game.Content.Load<Model>("tile");
		}

		public override void Update(GameTime gameTime)
		{
			base.Update(gameTime);
			gameWorldRotation =
				Matrix.CreateRotationX(MathHelper.ToRadians(RotationX)) *
				Matrix.CreateRotationY(MathHelper.ToRadians(RotationY));
		}

		public override void Draw(GameTime gameTime)
		{
			Matrix[] transforms = new Matrix[_tileModel.Bones.Count];
			float aspectRatio = Game.GraphicsDevice.Viewport.AspectRatio;
			_tileModel.CopyAbsoluteBoneTransformsTo(transforms);
			Matrix projection =
				Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45.0f),
				aspectRatio, 1.0f, 10000.0f);
			Matrix view = Matrix.CreateLookAt(new Vector3(0.0f, 50.0f, Zoom),
				Vector3.Zero, Vector3.Up);

			foreach (ModelMesh mesh in _tileModel.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.EnableDefaultLighting();

					effect.View = view;
					effect.Projection = projection;
					effect.World = gameWorldRotation *
						transforms[mesh.ParentBone.Index] *
						Matrix.CreateTranslation(Position);
				}
				mesh.Draw();
			}
			base.Draw(gameTime);
		}
	}
}
