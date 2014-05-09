using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace XNAFrontend.Components
{
	/// <summary>
	/// 3D board representation of the karo board game.
	/// </summary>
	internal class Board : DrawableGameComponent
	{
		private Vector3 _position;
		private Vector3 _modelPosition;
		private Model _tileModel;
		private float _modelRotation;
		private float _aspectRatio;

		private KaroGame KaroGame { get { return (KaroGame)this.Game; } }

		public Board(KaroGame game)
			: base(game)
		{
		}

		protected override void LoadContent()
		{
			base.LoadContent();
			_tileModel = Game.Content.Load<Model>("tile");
			_aspectRatio = Game.GraphicsDevice.Viewport.AspectRatio;
		}

		public override void Update(GameTime gameTime)
		{
			base.Update(gameTime);
		}

		public override void Draw(GameTime gameTime)
		{
			if (_tileModel == null)
			{
				LoadContent();
				return;
			}
			Matrix[] transforms = new Matrix[_tileModel.Bones.Count];
			_tileModel.CopyAbsoluteBoneTransformsTo(transforms);

			// Draw the model. A model can have multiple meshes, so loop.
			foreach (ModelMesh mesh in _tileModel.Meshes)
			{
				// This is where the mesh orientation is set, as well 
				// as our camera and projection.
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.EnableDefaultLighting();
					effect.World = transforms[mesh.ParentBone.Index] *
						Matrix.CreateRotationY(_modelRotation)
						* Matrix.CreateTranslation(_modelPosition);
					effect.View = Matrix.CreateLookAt(KaroGame.CameraPosition,
						Vector3.Zero, Vector3.Up);
					effect.Projection = Matrix.CreatePerspectiveFieldOfView(
						MathHelper.ToRadians(45.0f), _aspectRatio,
						1.0f, 10000.0f);
				}
				// Draw the mesh, using the effects set above.
				mesh.Draw();
			}
			base.Draw(gameTime);
		}
	}
}
