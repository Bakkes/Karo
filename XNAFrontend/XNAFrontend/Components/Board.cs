﻿using Microsoft.Xna.Framework;
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

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					foreach (ModelMesh mesh in _tileModel.Meshes)
					{
						foreach (BasicEffect effect in mesh.Effects)
						{
							effect.EnableDefaultLighting();
							effect.World = transforms[mesh.ParentBone.Index] *
								Matrix.CreateTranslation(Position + new Vector3(-300 * j, 0, -300 * i));
							effect.View = KaroGame.ViewMatrix;
							effect.Projection = KaroGame.ProjectionMatrix;
						}
						mesh.Draw();
					}
				}
			}
			base.Draw(gameTime);
		}
	}
}
