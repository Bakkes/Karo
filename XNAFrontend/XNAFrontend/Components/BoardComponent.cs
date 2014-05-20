using engine.wrapper;
using KaroManager;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace XNAFrontend.Components
{
	/// <summary>
	/// 3D board representation of the karo board game.
	/// </summary>
    internal class Board : ACommonComponent
	{
		private Model _tileModel;
        public CameraComponent CameraComponent{get; set;}

	
		private KaroGameManager KaroGameManager
		{
			get
			{
				return karoGame.KaroGameManager;;
			}
		}

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
			_tileModel = Game.Content.Load<Model>("tile");
		}

		public override void Update(GameTime gameTime)
		{
			base.Update(gameTime);
		}

		public override void Draw(GameTime gameTime)
		{
			Matrix[] transforms = new Matrix[_tileModel.Bones.Count];
			_tileModel.CopyAbsoluteBoneTransformsTo(transforms);

			BoardWrapper board = KaroGameManager.Board;

			for (int i = 0; i < 21; i++)
			{
				for (int j = 0; j < 21; j++)
				{
                    if (i == 20)
                    {
                        continue;
                    }
                    if (j == 20)
                    {
                        break;
                    }
					CellWrapper cell = board.GetRelativeCellAt(new Vector2DWrapper(i, j));
					if (cell.HasTile())
					{
						DrawCellAt(cell, i, j);
					}
				}
			}
			base.Draw(gameTime);
		}

		/// <summary>
		/// Draws a tile with the specified relative position.
		/// </summary>
		private void DrawCellAt(CellWrapper cell, int x, int y)
		{
			Matrix[] transforms = new Matrix[_tileModel.Bones.Count];
			_tileModel.CopyAbsoluteBoneTransformsTo(transforms);
			foreach (ModelMesh mesh in _tileModel.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.EnableDefaultLighting();
					effect.World = transforms[mesh.ParentBone.Index] *
						Matrix.CreateTranslation(Position + new Vector3(-300 * y, 0, -300 * x));
					effect.View = CameraComponent.ViewMatrix;
					effect.Projection = CameraComponent.ProjectionMatrix;
				}
				mesh.Draw();
			}
		}
	}
}
