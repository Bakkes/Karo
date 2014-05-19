using System.Collections;
using System.Collections.Generic;
using System.Linq;
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
		public CameraComponent CameraComponent{get; set;}

		private ICollection<Cell> cells;
	
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
			cells = new LinkedList<Cell>();
		}

		public override void Initialize()
		{
			base.Initialize();
			this.Position = Vector3.Zero;
		}

		protected override void LoadContent()
		{
			base.LoadContent();
			Model tile = Game.Content.Load<Model>("tile");
			BoardWrapper board = KaroGameManager.Board;
			for (int i = 0; i < 21; i++)
			{
				for (int j = 0; j < 21; j++)
				{
					if (i == 20)
					{
						cells.Add(
							new Cell(){
								Position = new Vector2(i,j),
								Model = tile,
								CameraComponent = CameraComponent
							}
						);
						continue;
					}
					if (j == 20)
					{
						cells.Add(
							new Cell(){
								Position = new Vector2(i,j),
								Model = tile,
								CameraComponent = CameraComponent
							}
						);
						break;
					}

					cells.Add(
						new Cell(){
							CellWrapper = board.GetRelativeCellAt(new Vector2DWrapper(i, j)),
							Model = tile,
							CameraComponent = CameraComponent
						}
					);
				}
			}
		}

		public override void Update(GameTime gameTime)
		{
		}

		public override void Draw(GameTime gameTime){
			foreach(Cell cell in cells){
				cell.Render();
			}
			base.Draw(gameTime);
		}
	}
}
