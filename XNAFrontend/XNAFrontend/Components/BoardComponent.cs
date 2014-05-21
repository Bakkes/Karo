using engine.wrapper;
using KaroManager;
using XNAFrontend.Services;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.Collections.Generic;
using System.Linq;
using KaroManager.State;
using System.Diagnostics;

namespace XNAFrontend.Components
{
	/// <summary>
	/// 3D board representation of the karo board game.
	/// </summary>
	internal class Board : ACommonComponent
	{
		const float SIZE = 1f;
		const float GAP = 0.1f;

		private Model _tileModel;
		private Model _minModel;
		private Model _maxModel;

		private MouseState _previousMouseState;

		private KaroGameManager KaroGameManager
		{
			get
			{
				return karoGame.KaroGameManager;
			}
		}

		public Vector3 Position { get; set; }

		public Board(KaroGame game)
			: base(game)
		{
			this.Position = new Vector3((SIZE + GAP) * 2f, 0f, (SIZE + GAP) * 1.5f);
			//this.Position = Vector3.Zero;
			LoadContent();
		}

		public override void Initialize()
		{
			base.Initialize();
			this._previousMouseState = Mouse.GetState();
		}

		protected override void LoadContent()
		{
			base.LoadContent();
			_tileModel = Game.Content.Load<Model>("tile");
			_minModel = Game.Content.Load<Model>("piecemin");
			_maxModel = Game.Content.Load<Model>("piecemax");
		}

		public override void Update(GameTime gameTime)
		{
			MouseState mouseState = Mouse.GetState();
			if (mouseState.LeftButton == ButtonState.Pressed && _previousMouseState.LeftButton != ButtonState.Pressed)
			{
				Vector2 tilePosition = GetTileAtPixelPosition(mouseState.X, mouseState.Y);
				if (tilePosition.X != -1337)
				{
					karoGame.KaroGameManager.Update(
						new System.Drawing.Point((int)tilePosition.X, (int)tilePosition.Y)
					);
				}
			}
			base.Update(gameTime);
			
			_previousMouseState = mouseState;
		}

		protected Vector2 GetTileAtPixelPosition(int mouseX, int mouseY)
		{
			ICamera camera = (ICamera)Game.Services.GetService(typeof(ICamera));
			Vector3 nearSource = new Vector3((float)mouseX, (float)mouseY, 0f);
			Vector3 farSource = new Vector3((float)mouseX, (float)mouseY, 1f);
			Matrix world = Matrix.CreateTranslation(0, 0, 0);
			Vector3 nearPoint = GraphicsDevice.Viewport.Unproject(nearSource,
				camera.Projection, camera.View, world);
			Vector3 farPoint = GraphicsDevice.Viewport.Unproject(farSource,
				camera.Projection, camera.View, world);

			Vector3 direction = farPoint - nearPoint;
			direction.Normalize();
			Ray pickRay = new Ray(nearPoint, direction);

			float nearestDist = float.MaxValue;
			Vector2 nearest = new Vector2(-1337, -1337);

			for (int x = -1; x <= 20; x++)
			{
				for (int y = -1; y <= 20; y++)
				{
					BoundingBox b = Utilities.CreateBoundingBox(
						_tileModel, world * Matrix.CreateTranslation(
							new Vector3(x * (SIZE + GAP), 0, y * (SIZE + GAP))
						)
					);
					float? dist = pickRay.Intersects(b);
					if (dist != null && dist > 0 && dist < nearestDist)
					{
						nearestDist = (float)dist;
						nearest = new Vector2(x, y);
					}
				}
			}
			return nearest;
		}

		public override void Draw(GameTime gameTime)
		{
			karoGame.GraphicsDevice.DepthStencilState = DepthStencilState.Default;

			BoardWrapper board = KaroGameManager.Board;
			double width = board.GetDynamicSize().X;
			
			System.Console.WriteLine("test: " + width);

			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; i + j < 20; j++)
				{
					CellWrapper cell = board.GetRelativeCellAt(new Vector2DWrapper(i, j));
					
					if (cell.HasTile())
					{
						DrawCellAt(cell, i, j);
					}
					if (IsMarkedCell(cell.GetRelativePosition()))
					{
						DrawCellAt(cell, i, j, true);
					}
					
					
				}
			}
			base.Draw(gameTime);
		}

		/// <summary>
		/// Draws a tile with the specified relative position.
		/// </summary>
		private void DrawCellAt(CellWrapper cell, int x, int y, bool marked = false)
		{
			ICamera camera = (ICamera)Game.Services.GetService(typeof(ICamera));
			Matrix world = Matrix.CreateRotationX(MathHelper.ToRadians(-90));
			bool clickableTile = IsMarkedCell(cell.GetRelativePosition());
			foreach (ModelMesh mesh in _tileModel.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.EnableDefaultLighting();
					effect.World = world * Matrix.CreateTranslation(new Vector3(x * (SIZE + GAP), 0, y * (SIZE + GAP)));
					effect.View = camera.View;
					effect.Projection = camera.Projection;
					if (marked)
					{
						effect.Alpha = 0.2f;
					}
					else
					{
						effect.Alpha = 1f;
					}
					if (clickableTile || marked)
					{
						effect.DiffuseColor = new Vector3(1f, 1f, 1f);
					}
					else
					{
						effect.DiffuseColor = new Vector3(0.5f, 0.5f, 0.5f);
					}
				}

				mesh.Draw();
			}

			if (!cell.IsEmpty())
			{
				DrawPieceAt(cell, x, y);
			}
		}

		private void DrawPieceAt(CellWrapper cell, int x, int y)
		{
			// Nothing to draw if this cell is empty.
			if (cell.IsEmpty()) { return; }

			// Define the model of the piece we have to use (max/min).
			Model pieceModel = cell.IsMaxPiece() ? _maxModel : _minModel;
			Vector3 color = cell.IsMaxPiece() ? Color.Red.ToVector3() : Color.Green.ToVector3();
			ICamera camera = (ICamera)Game.Services.GetService(typeof(ICamera));
			Matrix[] transforms = new Matrix[_tileModel.Bones.Count];
			_tileModel.CopyAbsoluteBoneTransformsTo(transforms);
			bool marked = false;
			if (KaroGameManager.CurrentMove != null)
			{
				marked = KaroGameManager.CurrentMove.GetFromCell() ==
					cell.GetAbsolutePosition();
			}

			// Flip the piece if neccesary
			Matrix world = Matrix.CreateRotationX(MathHelper.ToRadians(-270));
			if (cell.IsFlipped())
			{
				world *= Matrix.CreateRotationX(MathHelper.ToRadians(180));
			}

			BoundingBox pieceBox = Utilities.CreateBoundingBox(pieceModel, world);
			BoundingBox tileBox = Utilities.CreateBoundingBox(pieceModel, world);
			float extraHeight = pieceBox.Max.Y / 2 + tileBox.Max.Y;

			// Draw the piece on the cell.
			foreach (ModelMesh mesh in pieceModel.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.EnableDefaultLighting();
					effect.World = world * Matrix.CreateTranslation(new Vector3(x * (SIZE + GAP), extraHeight, y * (SIZE + GAP)));
					effect.View = camera.View;
					effect.Projection = camera.Projection;
					if (marked)
					{
						effect.DiffuseColor = new Vector3(1f, 1f, 0f);
					}
					else
					{
						effect.DiffuseColor = color;
					}
				}
				mesh.Draw();
			}
		}

		private bool IsMarkedCell(Vector2DWrapper position)
		{
			BoardWrapper board = KaroGameManager.Board;
			MoveWrapper currentMove = KaroGameManager.CurrentMove;
			IKaroState currentState = KaroGameManager.CurrentState;

			if (currentState is PlaceState)
			{
				foreach (MoveWrapper legalMove in KaroGameManager.LegalMoves)
				{
					if (position == legalMove.GetToCell())
					{
						return true;
					}
				}
			}
			else if (currentState is PieceSourceState)
			{
				foreach (MoveWrapper legalMove in KaroGameManager.LegalMoves)
				{
					if (position == legalMove.GetFromCell())
					{
						return true;
					}
				}
			}
			else if (currentState is PieceDestinationState)
			{
				foreach (MoveWrapper legalMove in KaroGameManager.LegalMoves
					.Where(m => m.GetFromCell() == currentMove.GetFromCell()))
				{
					if (position == legalMove.GetToCell())
					{
						return true;
					}
				}
			}
			else if (currentState is CellSourceState)
			{
				foreach (MoveWrapper legalMove in KaroGameManager.LegalMoves
					.Where(m => m.GetFromCell() == currentMove.GetFromCell())
					.Where(m => m.GetToCell() == currentMove.GetToCell()))
				{
					if (position == legalMove.GetUsedCell())
					{
						return true;
					}
				}
			}

			return false;
		}
	}
}
