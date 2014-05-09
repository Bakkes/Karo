using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace XNAFrontend.Components
{
	/// <summary>
	/// 3D board representation of the karo board game.
	/// </summary>
	internal class Board : DrawableGameComponent
	{
		private Model _tileModel;

		private KaroGame KaroGame { get { return (KaroGame)this.Game; } }

		public Vector3 Position { get; set; }

		public Board(KaroGame game)
			: base(game)
		{
			LoadContent();
		}

		public override void Initialize()
		{
			base.Initialize();
			this.Position = Vector3.Zero;
		}

		protected override void LoadContent()
		{
			base.LoadContent();
			_tileModel = Game.Content.Load<Model>("pawnred");
		}

		public override void Update(GameTime gameTime)
		{
			base.Update(gameTime);
		}

		public override void Draw(GameTime gameTime)
		{
			Matrix[] transforms = new Matrix[_tileModel.Bones.Count];
			_tileModel.CopyAbsoluteBoneTransformsTo(transforms);

			foreach (ModelMesh mesh in _tileModel.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.EnableDefaultLighting();
					effect.World = transforms[mesh.ParentBone.Index] *
						Matrix.CreateTranslation(Position);
					effect.View = KaroGame.ViewMatrix;
					effect.Projection = KaroGame.ProjectionMatrix;
				}
				mesh.Draw();
			}
			base.Draw(gameTime);
		}
	}
}
